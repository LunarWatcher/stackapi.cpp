# Error handling

For the most part, the library tries to deal with most of the error handling, as well as backoff.

It's worth noting that not all errors are handled at this time, but that the amount of handled issues will grow as the library does.

The `APIConfig` Struct contains two config variables for error handling; `autoHandleBackoff` and `autoHandleDowntime`. If these are set to false, stackapi.cpp throws when these types of errors are encountered.

If they're set to true, the library sleeps for a few minutes, and then re-tries the last invoked request. **This means the main thread will be blocked** if either of these options are true, and the corresponding type of error occurs. If you run the API calls on the main thread, alongside a user interface, this means the UI will be blocked, and you'll likely want to set these options to false. In turn, you need to handle errors manually.

## Automatic error handling

If you don't disable config variables, many errors are automatically handled. At the time of writing, this is with the exception of specific errors returned by the API, caused by incorrect API calls (mainly programmer errors), as these primarily occur during development. Dealing with these kinds of errors are documented in the manual error handling section.

For automatic error handling, there's naturally not much to do. Don't set the config variables to false, and let the library do its thing.

However, in some cases, you may still want to do extra handling of these errors. For this, there's a configurable callback; `APIConfig::errorCallback`.

This callback is invoked for several reasons:

1. Proper errors; non-200 status codes (Cloudflare blocks the request, backoff violations, downtime, internet outage, etc.)
2. Other waits. At the time of writing, this only applies to respecting backoff before calling an API endpoint. These aren't hard errors, but if you're developing a user-oriented program, this can be used to let the user know they need to wait before the request can be made. 
3. Service restauration after the previous points; used to signal that whatever was previously reported has been resolved.

\#3 is a very specific use-case for particularly bots that keep track of whether or not a new error has happened to avoid double-reporting errors. It can also be used to do event-driven updates for the user to avoid having handling on every request made. However, the exact handling is up to each consumer application.

## Manual error handling

If automatic error handling is either disabled or unavailable for a given type of error, you'll get exceptions. For the most part, you'll get an `stackapi::APIException`[^1], which contains a few fields that can be used for manual error handling:
* message: A custom message supplied by stackchat
* errorMessage: the full response from the API endpoint. May or may not be JSON, may or may not say something useful
* statusCode: Either the HTTP status code, a modified HTTP status code (HTTP 400 becomes HTTP 500 if the respons isn't JSON; this is the only modified HTTP status code), or `error_id` parsed from the JSON response. 
* isHTTPStatus: Whether or not the statusCode is an HTTP status code, or an error_id corresponding to one of the API error codes.

See the [/errors](https://api.stackexchange.com/docs/errors) endpoint for documentation on values for `error_id`. Note that if you're using automatic error handling, 500, 502, and 503 are automatically handled, and don't require any custom logic. 

The use of exceptions does require the use of try-catches in the code, but it also (in my biased opinion) simplifies certain parts of the handling. For example, if you're using an endpoint that requires an access_token, and you want to handle access token errors, you can use:
```cpp
try {
    // Note that the NullStruct used here is purely because I don't care enough to look up the return value of this endpoint
    // In real code, you probably want to check the return value
    api.post<stackapi::NullStruct>("questions/1234/upvote");
} catch (APIException e) {
    if (!e.isHTTPStatus && e.statusCode >= 401 && e.statusCode <= 403) {
        // Notify the user that their token is bad
        // Note that you can parse e.errorMessage as JSON to get error_message from it, and append it to the message

    } else {
        // Unhandled; either handle it or just throw, or ignore it if you prefer
        throw;
    }
}
```

[^1]: At the time of writing, this is the only exception thrown. Some parts of the library throw std::runtime_error, but these are not in response to API calls, and are more often than not programmer errors.
