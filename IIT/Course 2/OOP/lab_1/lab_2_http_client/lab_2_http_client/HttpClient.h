//
//  HttpClient.h
//  lab_2_http_client
//
//  Created by Alex Kuk on 23.03.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface HttpClient : NSObject {
    IBOutlet NSTextView *output;
    IBOutlet NSTextField *url;
    IBOutlet NSComboBox *method;
}
- (IBAction)makeRequest:(id)sender;
- (IBAction)clear:(id)sender;
@end
