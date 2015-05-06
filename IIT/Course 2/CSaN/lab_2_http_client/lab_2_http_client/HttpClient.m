//
//  HttpClient.m
//  lab_2_http_client
//
//  Created by Alex Kuk on 23.03.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#import "HttpClient.h"

@implementation HttpClient
- (void)awakeFromNib {
    [method selectItemAtIndex:0];
    [[url window] makeFirstResponder:nil];
}
- (IBAction)makeRequest:(id)sender {
    NSString *requestMethod = [method objectValueOfSelectedItem];
    NSURL *requestUrl = [NSURL URLWithString: [url stringValue]];
    
    NSMutableURLRequest *tmpRequest = [NSMutableURLRequest requestWithURL:requestUrl];
    bool valid = [NSURLConnection canHandleRequest:tmpRequest];
    
    if (!valid) {
        [self showAlert:@"Url is not valid"];
        return;
    }
    
    if (![requestMethod length]) {
        [self showAlert:@"Select request method?"];
        return;
    }
    
    CFHTTPMessageRef request = [self buildRequest :requestUrl :requestMethod];
    [self log: [self dumpHttpMessage :request]];
    
    CFHTTPMessageRef response = [self performHTTPRequest: request];
    [self log: [self dumpHttpMessage :response]];
    
}

- (CFHTTPMessageRef)buildRequest:(NSURL *)requestUrl :(NSString *)requestMethod{
    return [self buildRequest :requestUrl :requestMethod :(NSData *)@""];
}
                                            
- (CFHTTPMessageRef)buildRequest:(NSURL *)requestUrl :(NSString *)requestMethod :(NSData *)postData {
    
    bool  isPost = ([requestMethod caseInsensitiveCompare:@"Post"] == NSOrderedSame);
    
    CFHTTPMessageRef request = CFHTTPMessageCreateRequest(kCFAllocatorDefault, (__bridge CFStringRef)requestMethod, (__bridge CFURLRef)requestUrl, kCFHTTPVersion1_0);
    
    
    CFHTTPMessageSetHeaderFieldValue(request, CFSTR("HOST"), (__bridge CFStringRef)[requestUrl host]);
    CFHTTPMessageSetHeaderFieldValue(request, CFSTR("Connection"), CFSTR("keep-alive"));
    
    if (isPost) {
        CFHTTPMessageSetBody(request, (__bridge CFDataRef)postData);
        CFHTTPMessageSetHeaderFieldValue(request, CFSTR("Content-Length"), (__bridge CFStringRef)[NSString stringWithFormat:@"%lu", (unsigned long)[postData length]]);
        CFHTTPMessageSetHeaderFieldValue(request, CFSTR("Content-Type"), CFSTR("charset=utf-8"));
    }
    
    return request;
}

- (CFHTTPMessageRef)performHTTPRequest:(CFHTTPMessageRef)request
{
    CFReadStreamRef requestStream = CFReadStreamCreateForHTTPRequest(kCFAllocatorDefault, request);
    CFReadStreamOpen(requestStream);
    
    NSMutableData *responseBytes = [NSMutableData data];
    
    CFIndex numBytesRead = 0 ;
    do
    {
        UInt8 buf[1024];
        numBytesRead = CFReadStreamRead(requestStream, buf, sizeof(buf));
        
        
        if(numBytesRead > 0) {
            [responseBytes appendBytes:buf length:numBytesRead];
        }
        
    } while(numBytesRead > 0);
    
    
    CFHTTPMessageRef response = (CFHTTPMessageRef)CFReadStreamCopyProperty(requestStream, kCFStreamPropertyHTTPResponseHeader);
    CFHTTPMessageSetBody(response, (__bridge CFDataRef)responseBytes);
    
    
    CFReadStreamClose(requestStream);
    CFRelease(requestStream);
    
    return response;
}

- (NSString *)dumpHttpMessage:(CFHTTPMessageRef)httpMessageRef {
    NSData *data = (NSData *)CFBridgingRelease(CFHTTPMessageCopySerializedMessage(httpMessageRef));
   return [[NSString alloc] initWithBytes:[data bytes] length:[data length] encoding:NSUTF8StringEncoding];
}

- (IBAction)clear:(id)sender {
    [output setString:@""];
}

- (void)showAlert:(NSString*)message {
    NSAlert *alert;
    alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"OK"];
    [alert setMessageText:message];
    [alert setAlertStyle:NSCriticalAlertStyle];
    [alert runModal];
}

- (void)log:(NSString*)message {
    NSString *content = [NSString stringWithFormat: @"%@\n\n%@", [output string], message];
    content = [content stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceAndNewlineCharacterSet]];
    [output setString: content];
    [output scrollRangeToVisible: NSMakeRange([[output string] length], 0)];
}
@end
