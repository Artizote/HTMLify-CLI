#ifndef CONFIG_H
#define CONFIG_H


//
// DEV_ENV -> Development Environment
// PROD_ENV -> Production Environment
//

#ifdef DEV_ENV
    #define API_URL_BASE "http://api.localhost:8000"
#endif

#ifdef PROD_ENV
    #define API_URL_BASE "https://api.htmlify.me"
#endif

//
// API version
//     /v1/foo/baar
//

#define DEFAULT_API_VERSION 1

#endif
