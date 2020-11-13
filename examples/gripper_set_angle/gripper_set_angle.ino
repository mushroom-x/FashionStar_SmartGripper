/**
 * 爪子角度控制指令测试(带功率约束) 
 * --------------------------
 * 作者: 阿凯|Kyle
 * 邮箱: xingshunkai@qq.com
 * 更新时间: 2020/11/14
 */
 
#include <SoftwareSerial.h>
#include "FashionStar_UartServoProtocal.h"  // 串口总线舵机通信协议
#include "FashionStar_UartServo.h"          // Fashion Star串口总线舵机
#include "FashionStar_SmartGripper.h"       // Fashion Star智能夹具

// 软串口的配置
#define SOFT_SERIAL_RX 6    // 软串口发送端的GPIO
#define SOFT_SERIAL_TX 7    // 软串口接收端的GPIO
#define SOFT_SERIAL_BAUDRATE 4800   // 软串口的波特率

// 串口总线舵机配置
#define SERVO_ID 4      //爪子对应的舵机ID号
#define BAUDRATE 115200 // 波特率

// 爪子的配置
#define SERVO_ANGLE_GRIPPER_OPEN 15.0   // 爪子张开时的角度
#define SERVO_ANGLE_GRIPPER_CLOSE -45.0 // 爪子闭合时的角度
#define GRIPPER_INTERVAL_MS 1000        // 爪子开启闭合的周期, ms
#define GRIPPER_MAX_POWER 400           // 爪子的最大功率

// 软串口初始化
SoftwareSerial softSerial(SOFT_SERIAL_RX, SOFT_SERIAL_TX); // 创建软串口
// 创建舵机的通信协议对象
FSUS_Protocal protocal(BAUDRATE);
// 创建舵机的实例
FSUS_Servo uservo(SERVO_ID, &protocal);
// 创建智能机械爪实例
FSGP_Gripper gripper(&uservo, SERVO_ANGLE_GRIPPER_OPEN,SERVO_ANGLE_GRIPPER_CLOSE);

void setup(){
    softSerial.begin(SOFT_SERIAL_BAUDRATE); // 软串口
    softSerial.println("Start To Test Gripper\n"); // 打印日志
    
    protocal.init();    // 舵机通信协议初始化    
    gripper.init();     // 爪子初始化
}

void loop(){
    softSerial.println("Gripper Close\n"); // 打印日志
    gripper.setAngle(SERVO_ANGLE_GRIPPER_CLOSE, interval, power);
    // TODO 在5s内是否掉落
    delay(10000); // 等待1s
    softSerial.println("Gripper Open\n"); // 打印日志
    gripper.setAngle(SERVO_ANGLE_GRIPPER_OPEN, interval, power);
}