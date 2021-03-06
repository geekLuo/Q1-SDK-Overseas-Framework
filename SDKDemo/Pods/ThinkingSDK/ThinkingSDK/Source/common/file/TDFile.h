//
//  TDFile.h
//  ThinkingSDK
//
//  Created by LiHuanan on 2020/9/8.
//  Copyright © 2020 thinkingdata. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@interface TDFile : NSObject
@property(strong,nonatomic) NSString* appid;
- (instancetype)initWithAppid:(NSString*)appid;
- (void)archiveIdentifyId:(NSString *)identifyId;
- (NSString*)unarchiveIdentifyID ;
- (NSString*)unarchiveAccountID ;
- (void)archiveUploadSize:(NSNumber *)uploadSize;
- (NSNumber*)unarchiveUploadSize;
- (void)archiveUploadInterval:(NSNumber *)uploadInterval;
- (NSNumber*)unarchiveUploadInterval;
- (void)archiveAccountID:(NSString *)accountID;
- (void)archiveSuperProperties:(NSDictionary *)superProperties;
- (NSDictionary*)unarchiveSuperProperties;
- (void)archiveOptOut:(BOOL)optOut;
- (BOOL)unarchiveOptOut;
- (void)archiveIsEnabled:(BOOL)isEnabled;
- (BOOL)unarchiveEnabled;
- (BOOL)archiveObject:(id)object withFilePath:(NSString *)filePath;
- (BOOL)addSkipBackupAttributeToItemAtPath:(NSString *)filePathString;
// 兼容老版本
- (NSString*)unarchiveOldLoginId;
// 兼容老版本
- (void)deleteOldLoginId;
@end;

NS_ASSUME_NONNULL_END
