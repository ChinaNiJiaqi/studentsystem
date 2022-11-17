/*学生成绩管理系统
*author:倪嘉棋
*version:1.2  2022.11.16
*添加了一个链表,入学年份默认为系统时间
*/

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include <time.h>

#define TOTALCOURSE 3 // 课程数量 

//函数声明
void PrintMenu(void);//菜单函数
void InputStudents(void);//信息录入
void SearchName(void);//根据姓名查询
void SearchId(void);//根据学号查询
void SearchCourse(void);
void DeleteStudent(void);//删除信息
void ModifyStudent(void);//修改信息
void ScoreSort(void);//根据成绩排序
void GpaSort(void);//根据GPA排序
void Swap(int j);//交换数据
void BubleSortScore(void);//总分的冒泡排序
void BubleSortId(void);
void BubleSortCourseScore(int j);//单门课成绩排序
void PrintInfor(void);//显示信息到屏幕
void handle(void);//统计信息
void Insert(void);//插入
void PrintToFiles(void);//输出到文件





// 课程信息
typedef struct theCourse{
    char courseName[30];// 课程名字
    double courseMaxScore;// 课程最高分
    double courseTotalScore;//课程总得分(中间量不输出)
    double courseAveScore;// 课程平均分
    int coursePoint;// 课程学分(固定值)
    int rank[5]; // 不及格....优秀 满分人数

}Course;
Course courseInfor[TOTALCOURSE];//TOTALCOURSE个课程信息

//课程信息
typedef struct aCourse{
    char courseName[30];// 课程名字
    double courseScore;// 所取得的课程分数
}stuCourse;

// 学生结构体
typedef struct aStudent{
    char name[12]; // 姓名
    int id; // 学号
    stuCourse course[10];//学生的第x门课的信息
    double totalScore;// 总分(中间量不输出)
    double aveScore;// 平均分
    double totalPoint;// 总绩点
    double avePoint;// 平均绩点
    int totalSPoint;
    struct aStudent *next;
        
}Student;
Student stu[60];

Student* Creat(void);
void SearchByList(Student *head);
void SearchByListB(Student *head);
void SearchByListC(Student *head);


int totalPoint;//总绩点(中间量)
int stuNum = 0;
int flagId[60];//学号标志数组,0没人,1有人



int main() {
    struct aStudent *head, *node, *end;
    head = (Student*)malloc(sizeof(struct aStudent));

    

    //初始化课程名称
    strcpy(courseInfor[0].courseName,"C语言程序设计");    courseInfor[0].coursePoint = 5;
    strcpy(courseInfor[1].courseName, "高等数学");         courseInfor[1].coursePoint = 4;
    strcpy(courseInfor[2].courseName, "数据结构");         courseInfor[2].coursePoint = 3;
    totalPoint = courseInfor[0].coursePoint + courseInfor[1].coursePoint + courseInfor[2].coursePoint;

    while (1)// 循环进行
    {
        
        system("CLS");//清屏

        //打印功能菜单
        PrintMenu();
        printf("\t\t\t\t请输入你要执行的操作:");
        char choice;
        scanf("%c",&choice);
        getchar();// 吸收冗余输入

        switch (choice)
        {
        case '1': //1录入学生信息
            InputStudents();
            head = Creat();
            break;

        case '2': //2查询学生信息
            int searchChoice;
            printf("\t\t\t\t1.按姓名查询  2.按学号查询  3.按课程查询\n");
            printf("\t\t\t\t链表版4.按学号查询  5.按姓名查询  6.按课程查询\n");
            printf("\t\t\t\t请选择你要查询的方式:");
            
            scanf("%d",&searchChoice);
            getchar();// 吸收冗余输入
            if(searchChoice == 1) SearchName();//1.按姓名查询
            if(searchChoice == 2) SearchId();//2.按学号查询
            if(searchChoice == 3) SearchCourse();//课程
            if(searchChoice == 4) SearchByList(head);//测试 链表查询
            if(searchChoice == 5) SearchByListB(head);
            if(searchChoice == 6) SearchByListC(head);
            break;

        case '3': //3显示学生信息
            PrintInfor();
            break;

        case '4': //4删除学生信息
            DeleteStudent();
            head = Creat();
            break;

        case '5': //5修改学生信息
            ModifyStudent();
            head = Creat();
            
            break;
        
        case '6':// 6信息的统计
            handle();
            break;
        case '7':// 插入学生信息
            Insert();
            break;
        case '8':// 将数据写入文件
        
            PrintToFiles();
            break;

        case '0': //退出程序系统
            printf("欢迎再次使用！\n");
            return 0;
            break;
        
        default: //输入其他字符时报错
            system("ClS");
            printf("\t\t\t\t!!!您输入的选择有错误，请重新选择功能 !!!\n");
            break;
        }

    system("PAUSE");
    }
    
    return 0;
}

// 菜单
void PrintMenu(void){
    
    system("CLS");

    printf("\t\t\t\t=================================================  班级人数:%d\n",stuNum);
    printf("\t\t\t\t===============欢迎使用学生管理系统==============\n ");
    printf("\t\t\t\t=================================================\n");
    printf("\t\t\t\t=================请选择对应功能==================\n");
    printf("\t\t\t\t=================================================\n");
    printf("\t\t\t\t=\t\t1、 录入学生信息\t\t=\n");
    printf("\t\t\t\t=\t\t2、 查询学生信息\t\t=\n");
    printf("\t\t\t\t=\t\t3、 显示学生信息\t\t=\n");
    printf("\t\t\t\t=\t\t4、 删除学生信息\t\t=\n");
    printf("\t\t\t\t=\t\t5、 修改学生信息\t\t=\n");
    printf("\t\t\t\t=\t\t6、 统计学生信息\t\t=\n");
    printf("\t\t\t\t=\t\t7、 插入学生信息\t\t=\n");
    printf("\t\t\t\t=\t\t8、 数据写入文件\t\t=\n");

    printf("\t\t\t\t=\t\t0、 退出程序系统\t\t=\n");
    printf("\t\t\t\t=================================================\n");
    return ;
}

// 信息的录入
// 录入学生信息
void InputStudents(){

    int i;
    int j;
    
    

    //获取当前时间
    

    for(i = 0;i<60; i++) flagId[i] = 0;//初始话标志数组
    Student *head, *node, *end;
    node = (Student*)malloc(sizeof(struct aStudent));


    
    


    printf("\t\t\t\t请输入学生人数:");        
    scanf("%d", &stuNum);
    if(stuNum > 60) {printf("\t\t\t\t人数太多啦,我处理不过来了OnO!");return;}
    if(stuNum < 0) {printf("\t\t\t\t怎么还有负数啊!OnO!");return;}
    getchar();// 吸收冗余
    
    
    for (i = 0; i < stuNum; i++) {
        // 学生信息的输入
        printf("\t\t\t\t请输入第%d个学生的姓名:",i+1);
        gets(stu[i].name);
        
        printf("\t\t\t\t请输入第%d个学生的学号:",i+1);
        scanf("%d",&stu[i].id);
        
        getchar();// 吸收冗余

        if(flagId[stu[i].id-1] == 1){printf("\t\t\t\t学号怎么重复啦OnO!");return;}

        flagId[stu[i].id-1]=1;
       
        
        stu[i].totalSPoint = 0;// 初始化

        // 学生课程信息的输入
        for (j = 0; j < TOTALCOURSE; j++) {
            strcpy(stu[i].course[j].courseName , courseInfor[j].courseName);
            printf("\t\t\t\t%s",courseInfor[j].courseName);
            printf("\t请输入学生的成绩:",j+1);
            scanf("%lf",&stu[i].course[j].courseScore);
            getchar();// 吸收冗余

            courseInfor[j].courseTotalScore += stu[i].course[j].courseScore;
            courseInfor[j].courseAveScore = courseInfor[j].courseTotalScore /stuNum;//课程平均分的计算

            stu[i].totalScore += stu[i].course[j].courseScore;//学生的总分
            

            if(stu[i].course[j].courseScore >= 60) { 
            stu[i].totalPoint += (courseInfor[j].coursePoint * (stu[i].course[j].courseScore/10 - 5));// 总绩点
            stu[i].totalSPoint += courseInfor[j].coursePoint;//累计学生取得的学分
            }

            if (stu[i].course[j].courseScore == 100) courseInfor[j].rank[4]++;
            else if (stu[i].course[j].courseScore >= 85) courseInfor[j].rank[3]++;
            else if (stu[i].course[j].courseScore >= 70) courseInfor[j].rank[2]++;
            else if (stu[i].course[j].courseScore >= 60) courseInfor[j].rank[1]++;
            else {courseInfor[j].rank[0]++;
            stu[i].totalPoint += (courseInfor[j].coursePoint * 1);// 总绩点
            }
        }





        stu[i].avePoint = stu[i].totalPoint/totalPoint;//GPA
        stu[i].aveScore = stu[i].totalScore / TOTALCOURSE;//学生的平均分
    }
    

}

// 信息的查询
// 按姓名查询学生信息
void SearchName(){
    int i;
    int j;
    char name[20];
    printf("\t\t\t\t请输入你要查询的学生姓名:");
    gets(name);

    for(i = 0; i < stuNum; i++) {
        if(!strcmp(name,stu[i].name)) {

            printf("\t\t\t\t姓名:%s  ",stu[i].name);
            printf("学号:%d  ",stu[i].id);
            printf("平均分:%.2f  ",stu[i].aveScore);
            printf("平均绩点:%.2f\n\t\t\t\t",stu[i].avePoint);
            for (j = 0; j < TOTALCOURSE; j++) {
                printf("%s:%.2f  ",stu[i].course[j].courseName,stu[i].course[j].courseScore);
            }
        }
    }

}

// 按学号查询学生信息
void SearchId(){
    int i;
    int j;
    int id;
    int flag = 1;
    printf("\t\t\t\t请输入你要查询的学生学号:");
    scanf("%d",&id);
    getchar();// 吸收冗余

    for(i = 0; i < stuNum; i++) {
        if(id == stu[i].id) {
            
            flag--;
            printf("\t\t\t\t姓名:%s  ",stu[i].name);
            printf("学号:%d  ",stu[i].id);
            printf("平均分:%.2f  ",stu[i].aveScore);
            printf("平均绩点:%.2f\n\t\t\t\t",stu[i].avePoint);
            for (j = 0; j < TOTALCOURSE; j++) {
                printf("%s:%.2f  ",stu[i].course[j].courseName,stu[i].course[j].courseScore);
            }
        }
        
    }
    if(flag)printf("\t\t\t\t未找到匹配数据");


}

// 按课程查询学生信息
void SearchCourse(){
    int i;
    int j;
    char course[20];
    printf("\t\t\t\t请输入你要查询的课程:");
    gets(course);

    for(j = 0; j < TOTALCOURSE; j++) {
        if(!strcmp(course,courseInfor[j].courseName)) {
            for (i = 0; i < stuNum; i++) {
                printf("\t\t\t\t姓名:%s  ",stu[i].name);
                printf("学号:%d  ",stu[i].id);
                printf("分数:%.2f\n  ",stu[i].course[j].courseScore);
                

            
            }
            
            
        }
    }
}

// 信息的删除
// 删除学生信息
void DeleteStudent() {
    int flag = 1;
    int i;
    int j;
    char name[20];
    int id;
    printf("\t\t\t\t请输入你要删除的学生的姓名:");
    gets(name);
    printf("\t\t\t\t请输入你要删除的学生的学号:");
    scanf("%d",&id);
    getchar();
    

    for(i = 0; i < stuNum; i++) {
        if(!strcmp(name,stu[i].name) && id == stu[i].id && flag){//如果找到匹配的学生
            

            //由删除引起的课程总分,平均分,各等级人数的变化
            for(j = 0; j < TOTALCOURSE; j++) {
            courseInfor[j].courseTotalScore -= stu[i].course[j].courseScore;
            if (stu[i].course[j].courseScore == 100) courseInfor[j].rank[4]--;
            else if (stu[i].course[j].courseScore >= 85) courseInfor[j].rank[3]--;
            else if (stu[i].course[j].courseScore >= 70) courseInfor[j].rank[2]--;
            else if (stu[i].course[j].courseScore >= 60) courseInfor[j].rank[1]--;
            else courseInfor[j].rank[0]--;
            }
            courseInfor[j].courseAveScore = courseInfor[j].courseTotalScore /stuNum;

            //删除导致的学生结构体数组的变化
            for(i;i < stuNum-i+1;i++) {
                stu[i].avePoint = stu[i+1].avePoint;
                stu[i].aveScore = stu[i+1].aveScore;
                stu[i].totalPoint = stu[i+1].totalPoint;
                stu[i].totalScore = stu[i+1].totalScore;
                stu[i].totalSPoint = stu[i+1].totalSPoint;
                strcpy(stu[i].name,stu[i+1].name);
                for(j = 0; j < TOTALCOURSE; j++) {
                    stu[i].course[j].courseScore = stu[i+1].course[j].courseScore;
                }
                
            }

            stuNum--;
            flag--;
            flagId[stuNum-1] = 0;
        }
    }

    if(flag) {printf("\t\t\t\t未找到匹配的数据!");}
}

// 信息的修改
// 修改学生信息
void ModifyStudent() {
    int i;
    int j;
    int flag = 1;
    int choice;
    int selectCourse;
    char name[20];
    int id;
    double score;

    printf("\t\t\t\t请输入你要修改的学生的姓名:");
    gets(name);
    printf("\t\t\t\t请输入你要修改的学生的学号:");
    scanf("%d",&id);
    getchar();
    for(i = 0; i < stuNum; i++) {
        if(!strcmp(name,stu[i].name) && id == stu[i].id && flag){
            flag--;
            printf("\t\t\t\t1.学生姓名 2.课程成绩 \n"); 
            printf("\t\t\t\t请输入你要修改的学生数据:");
            scanf("%d",&choice);   getchar();//吸收冗余
            switch(choice){
                case 1:
                    printf("\t\t\t\t%s的姓名修改为:",stu[i].name);
                    gets(name);
                    strcpy(stu[i].name,name);
                    break;
                case 2:
                {
                    for(j = 0; j < TOTALCOURSE; j++)  printf("\t\t\t\t%d.%s\n",j+1,stu[i].course[j].courseName);
                    printf("\t\t\t\t你要修改的课程是:");
                    scanf("%d",&selectCourse);   getchar();//吸收冗余
                    
                    printf("\t\t\t\t%s的成绩由 %.2f 修改为:",
                    stu[i].course[selectCourse-1].courseName,stu[i].course[selectCourse-1].courseScore);
                    scanf("%lf",&score);   getchar();//吸收冗余

                    //由修改引起的课程信息变化
                    if(selectCourse < TOTALCOURSE + 1 && selectCourse > 0) {
                    courseInfor[selectCourse-1].courseTotalScore -= stu[i].course[selectCourse-1].courseScore;
                    courseInfor[selectCourse-1].courseTotalScore += score;
                    courseInfor[selectCourse-1].courseAveScore  = 
                            courseInfor[selectCourse-1].courseTotalScore / stuNum;
                        
                    if (stu[i].course[selectCourse-1].courseScore == 100) courseInfor[selectCourse-1].rank[4]--;
                    else if (stu[i].course[selectCourse-1].courseScore >= 85) courseInfor[selectCourse-1].rank[3]--;
                    else if (stu[i].course[selectCourse-1].courseScore >= 70) courseInfor[selectCourse-1].rank[2]--;
                    else if (stu[i].course[selectCourse-1].courseScore >= 60) courseInfor[selectCourse-1].rank[1]--;
                    else courseInfor[j].rank[0]--;
                        
                    if (score == 100) courseInfor[selectCourse-1].rank[4]++;
                    else if (score >= 85) courseInfor[selectCourse-1].rank[3]++;
                    else if (score >= 70) courseInfor[selectCourse-1].rank[2]++;
                    else if (score >= 60) courseInfor[selectCourse-1].rank[1]++;
                    else courseInfor[j].rank[0]++;

                    stu[i].course[selectCourse-1].courseScore = score;
                    }
 
                }
            }
            break;

        }
    }
    if(flag) {printf("\t\t\t\t未找到匹配的数据!");}

}

//信息的处理
//按成绩排序
void ScoreSort(){
    int selectSort;
    char couName[20];
    int j;
    //选择排名方式
    printf("\t\t\t\t1.单科成绩排名(递减)\t");
    printf("2.总成绩排名(递减)\t");
    printf("3.按学号排序\n");
    printf("\t\t\t\t请输入想要的排名方式:");
    scanf("%d",&selectSort);     //选择排名方式
    getchar();//清除冗余
    if (selectSort == 1) {
        printf("\t\t\t\t请输入要排名的课程名称:");
        gets(couName);
        for (j = 0; j < TOTALCOURSE; j++) {
            if (strcmp(couName, courseInfor[j].courseName) == 0)
                break;
                BubleSortCourseScore(j);
        }
    
    }
    else if (selectSort == 2) BubleSortScore();
    else if(selectSort == 3 ) BubleSortId();
    else printf("\t\t\t\t输入错误");
        

}
//按GPA排序
void GpaSort(){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//是否发生交换
        for(j = stuNum-1; j > i;j--){
            if(stu[j].avePoint > stu[j-1].avePoint){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;

    }
}

//冒泡排序总分
void BubleSortScore(){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//是否发生交换
        for(j = stuNum-1; j > i;j--){
            if(stu[j].totalScore > stu[j-1].totalScore){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;

    }

}

//冒泡排序单门课程分数
void BubleSortCourseScore(int courseid){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//是否发生交换
        for(j = stuNum-1; j > i;j--){
            if(stu[j].course[courseid].courseScore > stu[j-1].course[courseid].courseScore){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;
    }
}
//按学号排序
void BubleSortId(){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//是否发生交换
        for(j = stuNum-1; j > i;j--){
            if(stu[j].id < stu[j-1].id){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;
    }
}

//交换两个学生结构体
void Swap(int j) {
    double temps;
    int tempId;
    char tempName[20];
    int i;

    tempId = stu[j].id;
    stu[j].id = stu[j-1].id;
    stu[j-1].id = tempId;
    
    temps = stu[j].avePoint;
    stu[j].avePoint = stu[j-1].avePoint;
    stu[j-1].avePoint = temps;

    temps = stu[j].totalPoint;
    stu[j].totalPoint = stu[j-1].totalPoint;
    stu[j-1].totalPoint = temps;

    temps = stu[j].aveScore;
    stu[j].aveScore = stu[j-1].aveScore;
    stu[j-1].aveScore = temps;

    temps = stu[j].totalScore;
    stu[j].totalScore = stu[j-1].totalPoint;
    stu[j-1].totalScore = temps;

    temps = stu[j].totalSPoint;
    stu[j].totalSPoint = stu[j-1].totalSPoint;
    stu[j-1].totalSPoint = temps;

    strcpy(tempName,stu[j].name);
    strcpy(stu[j].name,stu[j-1].name);
    strcpy(stu[j-1].name,tempName);

    for(i = 0; i<TOTALCOURSE; i++) {
        temps = stu[j].course[i].courseScore;
        stu[j].course[i].courseScore = stu[j-1].course[i].courseScore;
        stu[j-1].course[i].courseScore = temps;
    }
    


}

//信息的插入
void Insert() {
    int i = stuNum;
    int j;
    stuNum++;//总人数加1
        printf("\t\t\t\t请输入学生的姓名:");
        gets(stu[i].name);
        printf("\t\t\t\t请输入学生的学号:");
        scanf("%d",&stu[i].id);
        getchar();// 吸收冗余

        if(flagId[stu[i].id-1] == 1){
            printf("\t\t\t\t学号怎么重复啦OnO!");
            stuNum--;
            return;
            }
        flagId[stu[i].id-1]=1;
        stu[i].totalSPoint = 0;// 初始化

        // 学生课程信息的输入
        for (j = 0; j < TOTALCOURSE; j++) {
            strcpy(stu[i].course[j].courseName , courseInfor[j].courseName);
            printf("\t\t\t\t%s",courseInfor[j].courseName);
            printf("\t请输入学生的成绩:",j+1);
            scanf("%lf",&stu[i].course[j].courseScore);
            getchar();// 吸收冗余

            courseInfor[j].courseTotalScore += stu[i].course[j].courseScore;
            courseInfor[j].courseAveScore = courseInfor[j].courseTotalScore /stuNum;//课程平均分的计算

            stu[i].totalScore += stu[i].course[j].courseScore;//学生的总分
            

            if(stu[i].course[j].courseScore >= 60) { 
            stu[i].totalPoint += (courseInfor[j].coursePoint * (stu[i].course[j].courseScore/10 - 5));// 总绩点
            stu[i].totalSPoint += courseInfor[j].coursePoint;//累计学生取得的学分
            }

            if (stu[i].course[j].courseScore == 100) courseInfor[j].rank[4]++;
            else if (stu[i].course[j].courseScore >= 85) courseInfor[j].rank[3]++;
            else if (stu[i].course[j].courseScore >= 70) courseInfor[j].rank[2]++;
            else if (stu[i].course[j].courseScore >= 60) courseInfor[j].rank[1]++;
            else {courseInfor[j].rank[0]++;
            stu[i].totalPoint += (courseInfor[j].coursePoint * 1);// 总绩点
            }
        }
        stu[i].avePoint = stu[i].totalPoint/totalPoint;//GPA
        stu[i].aveScore = stu[i].totalScore / TOTALCOURSE;//学生的平均分
    

}


//信息的显示
//打印学生信息
void PrintInfor(){
    int i;
    int j;
    int flag = 0;
    int failFlag=0;
    for (i = 0; i < stuNum; i++) {
        printf("\t\t\t\t学号:%d  姓名:%s  平均分:%.2f  GPA:%.2f\n\t\t\t\t",stu[i].id,stu[i].name,stu[i].aveScore,stu[i].avePoint);
        for(j = 0; j < TOTALCOURSE; j++) {
            printf("%s:%.2f  ",stu[i].course[j].courseName,stu[i].course[j].courseScore);
            if(stu[i].course[j].courseScore < 60) {
                flag = 1;
                stu[i].course[j].courseScore;
                failFlag++;
            }
            
        }
        if(flag == 1) printf("\n\t\t\t\t挂科数量:%d\n",failFlag);
        failFlag=0;
        printf("\n");
    }
}

//写入文件
void PrintToFiles() {
    FILE *fb;
    FILE *cfb;
    int i = 0; 
    int j;
    
    if ((fb = fopen("G:\\Cou Des of Pro\\studentfiles.txt", "w")) == NULL) {
        printf("打开文件: studentfiles.txt 失败!!!\n");
        exit(0);        //exit(0)表示正常运行程序并退出
    }

    fprintf(fb, "全体学生信息:\n");
    fprintf(fb, "---学号-------姓名-");
    for (j = 0;j < TOTALCOURSE;j++) {fprintf(fb,"-----");fprintf(fb,"%s",courseInfor[j].courseName);}
    fprintf(fb, "-------平均分-----GPA----");
    fprintf(fb, "\n");

    while (i < stuNum) {//输出学生信息
        fprintf(fb, "%8d", stu[i].id);
        fprintf(fb, "%15s", stu[i].name);
        for (j = 0;j < TOTALCOURSE;j++) {
            fprintf(fb, "%20.2f", stu[i].course[j].courseScore);
        }
        fprintf(fb, "%20.2f", stu[i].aveScore);
        fprintf(fb, "%12.2f", stu[i].avePoint);
        i++;
        fprintf(fb, "\n");

    }                //输出学生信息

    fclose(fb);

    if ((cfb = fopen("G:\\Cou Des of Pro\\coursefiles.txt", "w")) == NULL) {
        fprintf(cfb,"打开文件: coursefiles.txt 失败!!!\n");
        exit(0);        //exit(0)表示正常运行程序并退出
    }
    fprintf(cfb, "\t  \t平均分-----优秀率-----挂科率\n");
    
    
    for (j = 0;j < TOTALCOURSE;j++) {
        fprintf(cfb,"%20s",courseInfor[j].courseName);
        fprintf(cfb,"%10.2f",courseInfor[j].courseAveScore);
        fprintf(cfb,"%10.2f",(float)courseInfor[j].rank[4]/stuNum*100);
        fprintf(cfb,"%%");
        fprintf(cfb,"%10.2f",(float)courseInfor[j].rank[0]/stuNum*100);
        fprintf(cfb,"%%");
        fprintf(cfb,"\n");
    }
    fclose(cfb);

}
//统计信息
void handle(){
    int choice;
    int selectcourse;
    int j;
    printf("\t\t\t\t1.排序  2.课程数据  \n");
    printf("\t\t\t\t你要进行的操作是:");
    scanf("%d",&choice); getchar();
    if(choice == 1)  ScoreSort();
    else if (choice == 2){
        printf("\t\t\t\t");
        for(j=0; j < TOTALCOURSE; j++) printf("%d.%s",j+1,courseInfor[j].courseName);
        printf("\n\t\t\t\t你要查看的课程是:");
        scanf("%d",&selectcourse); getchar();
        if(selectcourse >3) { printf("\t\t\t\t输入错误!!!");    return;}
        
        printf("\t\t\t\t%s",courseInfor[selectcourse-1].courseName);
        printf("  平均分:%.2f",courseInfor[selectcourse-1].courseAveScore);
        printf("  优秀率:%.2f%%",courseInfor[selectcourse-1].rank[4]/(float)stuNum * 100);
        printf("  不及格率:%.2f%%\n",courseInfor[selectcourse-1].rank[0]/(float)stuNum * 100);
    }
   else printf("\t\t\t\t输入错误");
}

//链表相关函数
Student* Creat(){
    Student *head, *node,*end;
    int i,j;

    for (i = 0; i< stuNum;i++) {
        node = (Student*)malloc(sizeof(struct aStudent));
        node->id = stu[i].id;
        node->avePoint = stu[i].avePoint;
        node->aveScore = stu[i].aveScore;
        strcpy(node->name,stu[i].name);
        for (j = 0; j< TOTALCOURSE;j++) {
            node->course[j].courseScore = stu[i].course[j].courseScore;
            
        }
        
        node->next = NULL;
        if(i == 0)  head=end=node;
        else{
            end->next = node;
            end = node;
        }
    }
   return(head);

}

//链表的查询
//学号
void SearchByList(Student *head){
    Student *node=NULL;
    int id;
    int flag=1;
    printf("\t\t\t\t请输入他的学号:");
    scanf("%d",&id);  getchar();
    node = head;
    if(head !=NULL){
        do{
            if(node->id == id){
                printf("\t\t\t\t学号:%d  姓名:%s",node->id,node->name);
                printf("  C语言程序设计:%.2f",node->course[0].courseScore);
                printf("  高等数学:%.2f",node->course[1].courseScore);
                printf("  数据结构:%.2f",node->course[2].courseScore);
                printf("  平均分:%.2f\n",node->aveScore);

                flag=0;
            }
            node=node->next;

        }while(node!= NULL);

    }
    if(flag)printf("\t\t\t\t未找到匹配数据");
}
//姓名
void SearchByListB(Student *head){
    Student *node=NULL;
    char name[20];
    int flag=1;
    printf("\t\t\t\t请输入他的姓名:");
    scanf("%s",&name); 
    node = head;
    if(head !=NULL){
        do{
            if(!strcmp(name,node->name)){
                printf("\t\t\t\t学号:%d  姓名:%s",node->id,node->name);
                printf("  C语言程序设计:%.2f",node->course[0].courseScore);
                printf("  高等数学:%.2f",node->course[1].courseScore);
                printf("  数据结构:%.2f",node->course[2].courseScore);
                printf("  平均分:%.2f\n",node->aveScore);

                flag=0;
            }
            node=node->next;

        }while(node!= NULL);

    }
    if(flag)printf("\t\t\t\t未找到匹配数据");
}
//课程
void SearchByListC(Student *head){
    Student *node=NULL;
    int course;
    int flag=1;
    printf("\t\t\t\t0.C语言程序设计  1.高等数学  2.数据结构\n");
    printf("\t\t\t\t请输入课程:");
    scanf("%d",&course); getchar(); 
    node = head;
    if(head !=NULL){
        do{
            
                printf("\t\t\t\t学号:%d  姓名:%s",node->id,node->name);
                if (course == 0)  printf("  C语言程序设计:%.2f",node->course[0].courseScore);
                if (course == 1) printf("  高等数学:%.2f",node->course[1].courseScore);
                if (course == 2) printf("  数据结构:%.2f",node->course[2].courseScore);
                 printf("  平均分:%.2f\n",node->aveScore);

                flag=0;
            
            node=node->next;

        }while(node!= NULL);

    }
    if(flag)printf("\t\t\t\t未找到匹配数据");
}

