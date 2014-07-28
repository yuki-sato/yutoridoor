//
//  main.c
//  yutoridoor
//
//  Created by oyabunn on 2014/07/25.
//  Copyright (c) 2014年 yuki-sato. All rights reserved.
//

#include "cweb/cweb.h"

#include <string.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    CWebListen(9000);
    return 1;
}

void didReceiveCWebRequest(CWebTCPConnection *connection, CWebHTTPRequest *request)
{
    CWebHTTPResponse *response=NULL;
    char *html = NULL;
    if(CWebRequestMatch(request, "GET", "/")){
        CWebObject *obj = CWebObjectCreateDictionaryStringValueWithCopy("title", "/");
        html = CWebRenderHTML("./index.html", obj);
        CWebObjectFree(obj);
        response = CWebResponseCreateWithHTMLBODY(&html);
        
    }else{
        html = CWebRenderHTML("./404.html", NULL);
        response = CWebResponseCreateWithHTMLBODY(&html);
        response->statusCode = 404;
    }
    CWebResponse(connection, response);
    CWebResponseFree(response);
}