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

#include <wiringPi.h>

#define GPIO_LED 18
#define GPIO_PWM 15

int main(int argc, char *argv[])
{
    if(wiringPiSetupGpio() == -1){
        printf("\nGPIO Error");
        return 1;
    }
    pinMode(GPIO_LED, OUTPUT);
//    pinMode(GPIO_PWM, PWM_OUTPUT); //setup hardware pwm
     softPwmCreate(GPIO_PWM, 0, 100);
    
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
        
    }else if(CWebRequestMatch(request, "GET", "/led/on")){
        digitalWrite(GPIO_LED, 1);
        CWebObject *obj = CWebObjectCreateDictionaryStringValueWithCopy("title", "/led/on");
        html = CWebRenderHTML("./index.html", obj);
        CWebObjectFree(obj);
        response = CWebResponseCreateWithHTMLBODY(&html);
        
    }else if(CWebRequestMatch(request, "GET", "/led/off")){
        digitalWrite(GPIO_LED, 0);
        CWebObject *obj = CWebObjectCreateDictionaryStringValueWithCopy("title", "/led/off");
        html = CWebRenderHTML("./index.html", obj);
        CWebObjectFree(obj);
        response = CWebResponseCreateWithHTMLBODY(&html);
        
    }else if(CWebRequestMatch(request, "GET", "/pwm/right")){
//        pwmWrite(GPIO_PWM, 512);
        softPwmWrite(GPIO_PWM, 10);
        CWebObject *obj = CWebObjectCreateDictionaryStringValueWithCopy("title", "/pwm/right");
        html = CWebRenderHTML("./index.html", obj);
        CWebObjectFree(obj);
        response = CWebResponseCreateWithHTMLBODY(&html);
        
    }else if(CWebRequestMatch(request, "GET", "/pwm/left")){
//        pwmWrite(GPIO_PWM, 10);
        softPwmWrite(GPIO_PWM, 1);
        CWebObject *obj = CWebObjectCreateDictionaryStringValueWithCopy("title", "/pwm/left");
        html = CWebRenderHTML("./index.html", obj);
        CWebObjectFree(obj);
        response = CWebResponseCreateWithHTMLBODY(&html);
        
    }else {
        html = CWebRenderHTML("./404.html", NULL);
        response = CWebResponseCreateWithHTMLBODY(&html);
        response->statusCode = 404;
    }
    CWebResponse(connection, response);
    CWebResponseFree(response);
}