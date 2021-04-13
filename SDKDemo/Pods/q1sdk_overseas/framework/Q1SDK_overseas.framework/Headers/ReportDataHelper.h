//
//  ReportDataHelper.h
//  SDK
//
//  Created by mac on 2021/2/3.
//  Copyright © 2021 qqq. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *@brief 第三方上报中间层<数数>
 */

@interface ReportDataHelper : NSObject

/**
 * 初始化
 *
 * @param appId           数数appid
 * @param serverUrl  数数数据上报url
 */
+ (void)startWithAppId:(NSString *)appId serverUrl:(NSString *)serverUrl;

/**
 * 角色创建上报
 * @param serverId          服务器id
 * @param serverName     服务器名
 * @param roleId              角色ID
 * @param roleName          角色名
 * @param level                 等级，默认0
 * @param vipLevel          vip等级，默认0
 * @param gameUserId      游戏账号ID，跟渠道无关
 * @param user                   用户名或userid(通过session从服务器取)，账号ID加上带后缀的渠道
 * @param totalRevenue 累计充值的金额，第一次创建角色如果没有充值一般传0即可
 */
+ (void)createRole:(int)serverId
        serverName:(NSString *)serverName
            roleId:(int)roleId
          roleName:(NSString *)roleName
             level:(int)level
          vipLevel:(int)vipLevel
        gameUserId:(int)gameUserId
              user:(NSString *)user
      totalRevenue:(int)totalRevenue;
              
/**
 * 角色登录
 *
 * @param gameUserId   游戏的用户ID
 * @param roleId            角色id
 * @param roleName       角色名
 * @param level              角色等级
 * @param vipLevel       VIP等级
 * @param serverId       服务器id
 */
+ (void)login:(int)gameUserId
       roleId:(int)roleId
     roleName:(NSString *)roleName
        level:(int)level
     vipLevel:(int)vipLevel
     serverId:(int)serverId;

/**
 * 更改充值总额
 * @param num     金额
 */
+ (void)updateTotalRevenue:(int)num;

/**
 * 角色名字更新上报
 * @param rolename      新角色名字
 */
+ (void)updateName:(NSString *)rolename;

/**
 * 等级上报
 * @param level      等级，默认0
 */
+ (void)levelUp:(int)level;

/**
 * 上报VIP升级
 * @param vipLevel      等级，默认0
 */
+ (void)vipLevelUp:(int)vipLevel;


/**
 * 设置公共事件属性
 * @param properties 公共属性的json字符串
 */
+ (void)registerSuperProperties:(NSString *)properties;

/**
 * 自定义事件的统计方法，如购买商品，加入公会等，上报日志时带sdk内置公共参数
 * @param event  事件名称
 * @param propertie 事件属性
 */
+ (void)track:(NSString *)event propertie:(NSDictionary *)propertie;


// 清除一条公共事件属性
+ (void)unsetSuperProperty:(NSString *)property;

// 清除所有公共事件属性
+ (void)clearSuperProperties;

// 批量设置
+ (void)user_batchInfo:(NSString *)property;

// 设置用户属性(可变的：建议以latest_前缀开头)
+ (void)user_set:(NSDictionary *)property;

// 批量设置
+ (void)user_onceBatchInfo:(NSString *)property;

// 设置单次用户属性（不可变的：建议以first_开头）
+ (void)user_setOnce:(NSDictionary *)property;

// 对数值类型用户属性进行累加操作
+ (void)user_add:(NSDictionary *)property;

+ (void)user_add:(NSString *)propertyName propertyValue:(NSNumber *)propertyValue;

@end

