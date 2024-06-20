#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include<conio.h>
#define N 30
#define M 40

struct house{
    char member[15];     //所有者
    char user[15];       //使用者
    char mode[10];       //使用情况
}hou[N];                 //拟定总计房屋30套，缓冲用

struct volunteer{
    char name[15];   //志愿者姓名
    int hou_num;     //活动房屋
    int sTime;       //累计志愿时间
}vol[M];             //拟定志愿者最多40人，缓冲用

void input_hou_base();           //重置房屋信息
void lookALL_hou();              //查看所有房屋信息
void revise_hou();               //修改房屋信息
void search_hou();               //搜索房屋信息

void input_vol_base();           //追加志愿者信息
void sort_vol();                 //依据累计志愿时长从高到低排名志愿者信息
void lookALL_vol();              //查看所有志愿者信息
void revise_vol();               //修改志愿者信息
void search_vol();               //搜索志愿者信息
void delete_vol();               //删除志愿者信息

int passwordf();                 //密码系统
void system_house();             //房屋系统
void system_volunteer();         //志愿者系统

void input_hou_base(){
    FILE *fp=fopen("house.txt","w");
    if(fp==NULL){
        printf("数据获取失败！即将退出系统！\n");
        Sleep(5000);
        exit(0);
    }
    struct house temp;      //暂时存储
    char code[]="暂无";
    int choice;     //用于选择模式
    printf("请选择输入模式（一键输入输1，手动输入输2）：");
    scanf("%d",&choice);
    if(choice==1){
        strcpy(temp.member,code);
        strcpy(temp.user,code);
        strcpy(temp.mode,code);
        for(int i=0;i<N;i++){
            fwrite(&(temp),sizeof(struct house),1,fp);
        }
    }//1，将N栋房屋信息全转化为空
    else if(choice==2){
        for(int i=0;i<N;i++){
            printf("请输入第%d号房屋所有者姓名：",i+1);
            scanf("%s",temp.member);
            printf("请输入第%d号房屋使用者姓名：",i+1);
            scanf("%s",temp.user);
            printf("请输入第%d号房屋状态：",i+1);
            scanf("%s",temp.mode);
            fwrite(&(temp),sizeof(struct house),1,fp);
        }
    }//2，一个一个输N栋房屋的信息
    else{
        printf("\n请输入正确数字！\n");
    }
    fclose(fp);
}
void lookALL_hou(){
    FILE *fp=fopen("house.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！\n");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&hou[num],sizeof(struct house),1,fp);
    while(r){
        num++;
        r=fread(&hou[num],sizeof(struct house),1,fp);
    }       //将N栋房屋信息全储存在缓冲里
    fclose(fp);
    int count=0;
    while(count<num){
        printf("\n房屋%d\n",count+1);
        printf("所有者：%-20s使用者：%-20s状态：%-15s",hou[count].member,hou[count].user,hou[count].mode);
        count++;
    }       //全部显示
}
void revise_hou(){
    FILE *fp=fopen("house.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！\n");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&hou[num],sizeof(struct house),1,fp);
    while(r){
        num++;
        r=fread(&hou[num],sizeof(struct house),1,fp);
    }       //将N栋房屋信息全储存在缓冲里
    fclose(fp);
    int choice,point_num;
    char input_member[15],input_user[15],input_mode[10];
    printf("请输入目标房屋：");
    scanf("%d",&point_num);
    if(point_num<N&&point_num>0){
        printf("请输入需要修改的信息类型（修改所有者信息请按1，修改使用者及住房状态请按2）：");
        scanf("%d",&choice);
        if(choice==1){
            printf("请输入新的所有者信息：");
            scanf("%s",input_member);
            strcpy(hou[point_num-1].member,input_member);
        }
        else if(choice==2){
            printf("请输入新的使用者姓名：");
            scanf("%s",input_user);
            strcpy(hou[point_num-1].user,input_user);
            printf("请输入新的房屋状态（居住/娱乐）：");
            scanf("%s",input_mode);
            strcpy(hou[point_num-1].mode,input_mode);
        }
        else{
            printf("\n请输入正确数字！\n");
        }       //对缓冲信息进行修改
    }
    else{
        printf("\n超出房屋号码范围！\n");
    }
    fp=fopen("house.txt","w");
    int count=0;
    while(count<N){
        fwrite(&hou[count],sizeof(struct house),1,fp);
        count++;
    }
    fclose(fp);     //用缓冲信息替代旧信息
}
void search_hou(){
    FILE *fp=fopen("house.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！\n");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&hou[num],sizeof(struct house),1,fp);
    while(r){
        num++;
        r=fread(&hou[num],sizeof(struct house),1,fp);
    }       //将N栋房屋信息全储存在缓冲里
    fclose(fp);
    int choice;
    printf("请输入指定的房屋号码：");
    scanf("%d",&choice);
    if(choice<=num&&choice>0){
        printf("所有者：%-20s使用者：%-20s状态：%-15s",hou[choice-1].member,hou[choice-1].user,hou[choice-1].mode);
    }
    else{
        printf("\n超出房屋号码范围！\n");
    }       //从缓冲中定位指定信息
}
void input_vol_base(){
    FILE *fp=fopen("volunteer.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    while(r){
        num++;
        r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    }       //将已有志愿者信息全储存在缓冲里
    fp=fopen("volunteer.txt","a+");
    struct volunteer temp;//暂时存储
    int judge=0;//用于判断是否有人重名
    printf("请输入新的志愿者姓名：");
    scanf("%s",temp.name);
    for(int i=0;i<num;i++){
        if(strcmp(vol[i].name,temp.name)==0){
            judge++;
        }
    }
    if(judge){
        printf("\n数据库里有人与之重名！请使用其他名称！");
    }
    else{
        printf("请输入其志愿房屋号码：");
        scanf("%d",&temp.hou_num);
        while(temp.hou_num<0||temp.hou_num>N){
            printf("超出可选范围！请重新输入！");
            scanf("%d",&temp.hou_num);
        }
        printf("请输入其累计志愿时长：");
        scanf("%d",&temp.sTime);
        fwrite(&(temp),sizeof(struct house),1,fp);    //将单个缓冲信息填入文件
    }
    fclose(fp);
    sort_vol();     //依据累计志愿时长排名志愿者信息
}
void sort_vol(){
    FILE *fp=fopen("volunteer.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    while(r){
        num++;
        r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    }       //将已有志愿者信息全储存在缓冲里
    fclose(fp);
    int iMAX;       //找到的最大值
    struct volunteer temp;      //缓冲介质
    for(int i=0;i<num;i++){
        iMAX=i;
        for(int j=i+1;j<num;j++){
            if(vol[j].sTime>vol[iMAX].sTime){
                iMAX=j;
            }
        }
        if(iMAX!=i){
            temp=vol[i];
            vol[i]=vol[iMAX];
            vol[iMAX]=temp;
        }
    }       //冒泡排序
    fp=fopen("volunteer.txt","w");
    int count=0;
    while(count<num){
        fwrite(&vol[count],sizeof(struct volunteer),1,fp);
        count++;
    }       //将排位后的缓冲信息替代旧信息
    fclose(fp);
}
void lookALL_vol(){
    FILE *fp=fopen("volunteer.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！\n");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    while(r){
        num++;
        r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    }       //将已有志愿者信息全储存在缓冲里
    fclose(fp);
    int count=0;
    while(count<num){
        printf("\n志愿者：%-20s活动房屋：%-5d累计志愿时长：%-5d",vol[count].name,vol[count].hou_num,vol[count].sTime);
        count++;
    }       //全部显示
}
void revise_vol(){
    FILE *fp=fopen("volunteer.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！\n");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    while(r){
        num++;
        r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    }       //将已有志愿者信息全储存在缓冲里
    fclose(fp);
    int choice,count=0,judge=0;
    char point_name[15],input_name[15];
    printf("请输入目标志愿者姓名：");
    scanf("%s",point_name);
    while(count<num){
        if(strcmp(point_name,vol[count].name)==0){      //定位到指定人物
           printf("请输入要修改的信息类型（姓名信息请输1，志愿活动房屋信息请输2，累计志愿时长信息请输3）：");
           scanf("%d",&choice);
           if(choice==1){
                printf("请输入新的姓名：");
                scanf("%s",input_name);
                for(int i=0;i<num;i++){
                    if(strcmp(vol[i].name,input_name)==0){
                        judge++;
                    }
                }
                if(judge){
                    printf("\n数据库里有人与之重名！请使用其他名称！");
                    break;
                }
                else{
                    strcpy(vol[count].name,input_name);
                }
           }
           else if(choice==2){
                printf("请输入新的志愿活动房屋：");
                scanf("%d",&vol[count].hou_num);
                while(vol[count].hou_num<0||vol[count].hou_num>N){
                    printf("\n超出可选范围！请重新输入：");
                    scanf("%d",&vol[count].hou_num);
                }
           }
           else if(choice==3){
                printf("请输入新的志愿时长：");
                scanf("%d",&vol[count].sTime);
           }
           else{
                printf("\n数据错误！");
           }
           break;       //打破循环，使count不达到num
        }
        count++;
    }
    if(count==num){
        printf("\n查无此人！\n");
    }
    fp=fopen("volunteer.txt","w");     //刷新fp
    int recount=0;
    while(recount<num){
        fwrite(&vol[recount],sizeof(struct volunteer),1,fp);
        recount++;
    }       //将缓冲信息替换旧信息
    fclose(fp);
    void sort_vol();     //依据累计志愿时长排名志愿者信息
}
void search_vol(){
    FILE *fp=fopen("volunteer.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！\n");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    while(r){
        num++;
        r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    }       //将已有志愿者信息全储存在缓冲里
    fclose(fp);
    char choice[15];
    int count;
    printf("请输入指定的志愿者姓名：");
    scanf("%s",choice);
    while(count<num){      //定位到指定人物
        if(strcmp(vol[count].name,choice)==0){
            printf("\n志愿者：%-20s活动房屋：%-5d累计志愿时长：%-5d",vol[count].name,vol[count].hou_num,vol[count].sTime);
            break;       //打破循环，使count不达到num
        }
        count++;
    }
    if(count==num){
        printf("\n查无此人！\n");
    }
}
void delete_vol(){
    FILE *fp=fopen("volunteer.txt","r");
    if(fp==NULL){
        printf("\n数据获取失败！即将退出系统！\n");
        sleep(5000);
        exit(0);
    }
    int r,num=0;
    r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    while(r){
        num++;
        r=fread(&vol[num],sizeof(struct volunteer),1,fp);
    }       //将已有志愿者信息全储存在缓冲里
    int choice,count=0,recount=0;
    char input_name[15];
    printf("请选择删除模式（全部删除请输1，定点删除请输2）：");
    scanf("%d",&choice);
    if(choice==1){
        fclose(fp);
        fp=fopen("volunteer.txt","w+");
        fclose(fp);
    }
    else if(choice==2){
        printf("请输入要删除的志愿者姓名：");
        scanf("%s",input_name);
        while(count<num){      //定位到指定人物
            if(strcmp(vol[count].name,input_name)==0){
                for(;count<num-1;count++){
                    strcpy(vol[count].name,vol[count+1].name);
                    vol[count].hou_num=vol[count+1].hou_num;
                    vol[count].sTime=vol[count+1].sTime;
                }
                fp=fopen("volunteer.txt","w");
                while(recount<num-1){
                    fwrite(&vol[recount],sizeof(struct volunteer),1,fp);
                    recount++;
                }
                fclose(fp);
                break;       //打破循环，使count不达到num
            }
        count++;
        }
        if(count==num){
            printf("\n查无此人！\n");
        }

    }

}
int passwordf(){
    char truePassword[]="10086",password[20],c;
    int count=0,recount=0;
    printf("您即将进入活力社区信息系统！请输入管理员密码：");
    while(recount!=3){
        count=0;
        c=getch();
        while(c!='\r'){
            if(c=='\b'){
                printf("\b \b");
                count--;
            }
            else{
                password[count]=c;  //将c内容物填充，组成用户输入的密码
                printf("*");
                count++;
            }
            c=getch();
        }
        if(strcmp(truePassword,password)==0){
            printf("\n密码正确！");
            return 1;       //比对用户输入的密码和真密码，正确则解锁
        }
        else{
            printf("\n密码错误！剩余%d次机会！请重试：",2-recount);
            recount++;      //不正确则重试
        }
    }
    printf("\n密码错误！即将退出！\n");
    return 0;       //3次输入错误后，程序将退出
}
void system_house(){
    int choice2;
    printf("请选择要实现的功能（退出请输0，重置房屋信息请输1，查看所有房屋信息请输2，修改房屋信息请输3，搜索房屋信息请输4）：");
    scanf("%d",&choice2);
        while(choice2){
            if(choice2==1){
            input_hou_base();
        }
        else if(choice2==2){
            lookALL_hou();
        }
        else if(choice2==3){
            revise_hou();
        }
        else if(choice2==4){
            search_hou();
        }
        else{
            printf("\n请输入正确数字！\n");
        }
        printf("\n请选择要实现的功能（退出请输0，重置房屋信息请输1，查看所有房屋信息请输2，修改房屋信息请输3，搜索房屋信息请输4）：");
        scanf("%d",&choice2);
    }

}
void system_volunteer(){
    int choice2;
    printf("请选择要实现的功能（退出请输0，追加志愿者信息请输1，查看所有志愿者信息请输2，修改志愿者信息请输3，搜索志愿者信息请输4，删除志愿者信息请输5）：");
    scanf("%d",&choice2);
    while(choice2){
        if(choice2==1){
            input_vol_base();
        }
        else if(choice2==2){
            lookALL_vol();
        }
        else if(choice2==3){
            revise_vol();
        }
        else if(choice2==4){
            search_vol();
        }
        else if(choice2==5){
            delete_vol();
        }
        else{
            printf("\n请输入正确数字！\n");
        }
        printf("\n请选择要实现的功能（退出请输0，追加志愿者信息请输1，查看所有志愿者信息请输2，修改志愿者信息请输3，搜索志愿者信息请输4，删除志愿者信息请输5）：");
        scanf("%d",&choice2);
    }
}
int main()
{
    int choice1;
    if(passwordf()){
        printf("\n请选择要操作的系统（退出请输0，房屋系统请输1，志愿者系统请输2）：");
        scanf("%d",&choice1);
        while(choice1){
            if(choice1==1){
                system_house();
            }
            else if(choice1==2){
                system_volunteer();
            }
            else{
                printf("\n请输入正确数字！\n");
            }
            printf("\n请选择要操作的系统（退出请输0，房屋系统请输1，志愿者系统请输2）：");
            scanf("%d",&choice1);
        }
    }
    exit(0);
}
