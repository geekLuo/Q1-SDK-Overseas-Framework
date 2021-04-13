//
//  ResponseModel.h
//  SDK
//
//  Created by ITMAC on 2019/3/21.
//  Copyright © 2019年 luo. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ResponseModel : NSObject
@property (nonatomic ,assign) NSInteger status;
@property (nonatomic ,strong) NSString *info;
@property (nonatomic ,strong) NSDictionary *responseDic;

- (void)setNetError;

@end


