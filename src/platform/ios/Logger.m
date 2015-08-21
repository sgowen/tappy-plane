//
//  Logger.m
//  tappyplane
//
//  Created by Stephen Gowen on 2/27/14.
//  Copyright (c) 2014 Gowen Game Dev. All rights reserved.
//

#import "Logger.h"

#define LOG_DEBUG @"DEBUG"
#define LOG_INFO @"INFO"
#define LOG_WARN @"WARN"
#define LOG_ERROR @"ERROR"

static int loggingLevel = 4;

@implementation Logger

+ (void)initializeLoggingLevelFromNSString:(NSString *)loggingLevelName
{
    if([loggingLevelName isEqualToString:LOG_DEBUG])
    {
        loggingLevel = 4;
    }
    else if([loggingLevelName isEqualToString:LOG_INFO])
    {
        loggingLevel = 3;
    }
    else if([loggingLevelName isEqualToString:LOG_WARN])
    {
        loggingLevel = 2;
    }
    else if([loggingLevelName isEqualToString:LOG_ERROR])
    {
        loggingLevel = 1;
    }
    else
    {
        loggingLevel = 0;
    }
}

- (id)initWithClass:(Class)c
{
    self = [super init];
    
    if(self)
    {
        TAG = NSStringFromClass(c);
    }
    
    return self;
}

- (void)debug:(NSString *)message
{
    if (loggingLevel >= 4)
    {
        NSLog(@"%@ [%@] %@", TAG, LOG_DEBUG, message);
    }
}

- (void)info:(NSString *)message
{
    if (loggingLevel >= 3)
    {
        NSLog(@"%@ [%@] %@", TAG, LOG_INFO, message);
    }
}

- (void)warn:(NSString *)message
{
    if (loggingLevel >= 2)
    {
        NSLog(@"%@ [%@] %@", TAG, LOG_WARN, message);
    }
}

- (void)error:(NSString *)message
{
    if (loggingLevel >= 1)
    {
        NSLog(@"%@ [%@] %@", TAG, LOG_ERROR, message);
    }
}

- (void)error:(NSString *)message withException:(NSException *)e
{
    if (loggingLevel >= 1)
    {
        NSLog(@"%@ [%@] %@, Exception: %@, Stack Trace: %@", TAG, LOG_ERROR, message, [e description], [e callStackSymbols]);
    }
}

- (void)error:(NSString *)message withError:(NSError *)e
{
    if (loggingLevel >= 1)
    {
        NSLog(@"%@ [%@] %@, Error: %@", TAG, LOG_ERROR, message, [e description]);
    }
}

+ (bool)isErrorEnabled
{
    return loggingLevel >= 1;
}

+ (bool)isWarnEnabled
{
    return loggingLevel >= 2;
}

+ (bool)isInfoEnabled
{
    return loggingLevel >= 3;
}

+ (bool)isDebugEnabled
{
    return loggingLevel >= 4;
}

@end
