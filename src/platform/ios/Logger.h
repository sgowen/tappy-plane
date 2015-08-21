//
//  Logger.h
//  tappyplane
//
//  Created by Stephen Gowen on 2/27/14.
//  Copyright (c) 2014 Gowen Game Dev. All rights reserved.
//

@interface Logger : NSObject
{
@private
    NSString *TAG;
}

+ (void)initializeLoggingLevelFromNSString:(NSString *)loggingLevelName;

- (id)initWithClass:(Class)c;

- (void)debug:(NSString *)message;

- (void)info:(NSString *)message;

- (void)warn:(NSString *)message;

- (void)error:(NSString *)message;

- (void)error:(NSString *)message withException:(NSException *)e;

- (void)error:(NSString *)message withError:(NSError *)e;

+ (bool)isErrorEnabled;

+ (bool)isWarnEnabled;

+ (bool)isInfoEnabled;

+ (bool)isDebugEnabled;

@end
