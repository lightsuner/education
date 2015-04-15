//
//  ViewController.m
//  lab_3_FTP_client
//
//  Created by Alex Kuk on 29.03.15.
//  Copyright (c) 2015 Alex. All rights reserved.
//

#import "ViewController.h"
@import AppKit;

@implementation ViewController {
    IBOutlet NSTableView *tableView;
}

- (void)awakeFromNib {
    currentDir = [NSHomeDirectory() stringByAppendingPathComponent: @"Pictures"];
    fileManager = [NSFileManager defaultManager];

}

- (IBAction)onClick1:(id)sender {
   NSArray *dirContent = [fileManager contentsOfDirectoryAtPath:currentDir error:nil];
    
    for (NSString * filePath in dirContent) {
        NSLog(@"URL: %@", filePath);

    }
}
@end
