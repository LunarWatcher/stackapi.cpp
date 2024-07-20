# stackapi.cpp

C++ library for using the [Stack Exchange API](//api.stackexchange.com). 

## Requirements

* A C++20 compiler

## API version support

| stackapi version | Main Stack Exchange API version | Other supported versions |
| --- | --- | --- |
| Up to and including v1.0.0 | [v2.3](https://api.stackexchange.com/docs) | Theoretically v2.2 |
| v2.0.0 and newer | [v3](https://api.stackexchange.com/v3/swagger/index.html) |

Note that the latest version of stackapi is aimed at the latest version of the API, if implemented. If you need to use an older version of the API, you need to use an older version of stackapi.cpp. Older versions of the API will not be getting updates or continued support. 

SE has also historically shut down older API versions. v1 of the API was permanently killed [with the release of v2.2](https://stackoverflow.blog/2014/02/10/stack-exchange-api-v2-2-and-the-demise-of-v1-x/), for example. This was two years after the release of v2.0. v2.3 is likely not going away as fast (due to it having been around for 12 years), but there's nothing new coming, and continug to develop for an API that's likely going away at some point in the future just for some legacy use-cases is not a good use of time.
