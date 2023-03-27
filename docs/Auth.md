# Auth

Auth is complicated.

Due to the varied applications, the library itself does not provide any methods to deal with this. This may change in the future, but for now, the following applies:

You need to figure out a way to get and store the auth key. The docs for getting it can be found [in the API docs](https://api.stackexchange.com/docs/authentication). However, here is a Linux-only example from a tool I've written (note: closed-source):

```cpp
const std::string OAUTH_VERIFICATION_URL = "https://stackoverflow.com";
const std::string OAUTH_URL = "https://stackoverflow.com/oauth/dialog?client_id=" + CLIENT_ID
    + "&scope=write_access,no_expiry&redirect_uri=" + OAUTH_VERIFICATION_URL;
```
```cpp
int main() {
    std::string token;
    if (!std::filesystem::exists(".oauth.txt")) {
        conf.log->info("No token found. Opening {}", Constants::OAUTH_URL);
        // xdg-open here is why this is Linux-only. 
        std::system((std::string("xdg-open '") + Constants::OAUTH_URL + "'").c_str());
        std::cout << "Paste your token here: ";
        std::getline(std::cin, token);
        std::ofstream stream(".oauth.txt");
        stream << token;
    } else {
        std::ifstream stream(".oauth.txt");
        stream >> token;
    }
    conf.log->info("Token loaded.");
    // ...
}
```

This will redirect the user to stackoverflow.com, where the token is then part of the URL. You _can_ use your own domain here, which makes more sense for web-based applications, but statistically, you're probably not when you're using C++. :)

Note that to use this URL, the OAuth domain has to be `stackoverflow.com`. Doing so, from what I've gathered, is fairly standard among open-source tools.

The code is based on the implicit OAuth flow, because it's convenient. Additionally, step 4 of the explicit OAuth request requires the client_secret, which should never, ever be posted in public, and it's very easy to fuck that up with a public application, and it isn't possible to deploy at a scale, shy of requiring everyone to register their own, separate application. It just doesn't scale.

## Using the token

As long as a token is passed, it's always supplied. The major advantage with this is not using the global IP-based quota, but using [one of your 5x10k user quotas](https://api.stackexchange.com/docs/throttle). Additionally, from my own observations, this doesn't result in nearly as many throttles when multiple apps are running, even if they're using different API keys.

The inner workings of the rate limiting algorithm are a tightly kept secret though, so it might just be a coincidence.

In either case, you should be able to run more stuff without it resulting in rate limits.

There are two ways to pass the token. As already seen with the API key, there is:
```cpp
stackapi::StackAPI api (
    {
        .apiKey{API_KEY},
        .auth{"69420"},
        // ...
    }
);
```

Which sets it globally. You can also set it per-endpoint:
```cpp
auto res = api.get<stackapi::Answer>("answers", {}, {
    .auth{"n3v3r g0nn4 giv3 y0u up"},
    .filter{"!*MjkmyT9x3lPk8ML"},
});
```

The primary advantage with this strategy is that, by using it on auth-only endpoints, you can potentially double your quota. This is only efficient if there's nothing else running on the same IP though, because of the previously mentioned observed rate limit increase.

Which you use is consequently not that important, as long as your program works optimally by whatever metrics you may have.

## Calling endpoints

Calling auth endpoints do not require anything special in the code when the auth token has been provided. As long as any required data is passed to the API, it's all good.

This also unlocks all the POST endpoints, as most/all of them are behind an auth wall.
