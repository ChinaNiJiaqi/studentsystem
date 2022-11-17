/*ѧ���ɼ�����ϵͳ
*author:�߼���
*version:1.2  2022.11.16
*�����һ������,��ѧ���Ĭ��Ϊϵͳʱ��
*/

#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include <time.h>

#define TOTALCOURSE 3 // �γ����� 

//��������
void PrintMenu(void);//�˵�����
void InputStudents(void);//��Ϣ¼��
void SearchName(void);//����������ѯ
void SearchId(void);//����ѧ�Ų�ѯ
void SearchCourse(void);
void DeleteStudent(void);//ɾ����Ϣ
void ModifyStudent(void);//�޸���Ϣ
void ScoreSort(void);//���ݳɼ�����
void GpaSort(void);//����GPA����
void Swap(int j);//��������
void BubleSortScore(void);//�ֵܷ�ð������
void BubleSortId(void);
void BubleSortCourseScore(int j);//���ſγɼ�����
void PrintInfor(void);//��ʾ��Ϣ����Ļ
void handle(void);//ͳ����Ϣ
void Insert(void);//����
void PrintToFiles(void);//������ļ�





// �γ���Ϣ
typedef struct theCourse{
    char courseName[30];// �γ�����
    double courseMaxScore;// �γ���߷�
    double courseTotalScore;//�γ��ܵ÷�(�м��������)
    double courseAveScore;// �γ�ƽ����
    int coursePoint;// �γ�ѧ��(�̶�ֵ)
    int rank[5]; // ������....���� ��������

}Course;
Course courseInfor[TOTALCOURSE];//TOTALCOURSE���γ���Ϣ

//�γ���Ϣ
typedef struct aCourse{
    char courseName[30];// �γ�����
    double courseScore;// ��ȡ�õĿγ̷���
}stuCourse;

// ѧ���ṹ��
typedef struct aStudent{
    char name[12]; // ����
    int id; // ѧ��
    stuCourse course[10];//ѧ���ĵ�x�ſε���Ϣ
    double totalScore;// �ܷ�(�м��������)
    double aveScore;// ƽ����
    double totalPoint;// �ܼ���
    double avePoint;// ƽ������
    int totalSPoint;
    struct aStudent *next;
        
}Student;
Student stu[60];

Student* Creat(void);
void SearchByList(Student *head);
void SearchByListB(Student *head);
void SearchByListC(Student *head);


int totalPoint;//�ܼ���(�м���)
int stuNum = 0;
int flagId[60];//ѧ�ű�־����,0û��,1����



int main() {
    struct aStudent *head, *node, *end;
    head = (Student*)malloc(sizeof(struct aStudent));

    

    //��ʼ���γ�����
    strcpy(courseInfor[0].courseName,"C���Գ������");    courseInfor[0].coursePoint = 5;
    strcpy(courseInfor[1].courseName, "�ߵ���ѧ");         courseInfor[1].coursePoint = 4;
    strcpy(courseInfor[2].courseName, "���ݽṹ");         courseInfor[2].coursePoint = 3;
    totalPoint = courseInfor[0].coursePoint + courseInfor[1].coursePoint + courseInfor[2].coursePoint;

    while (1)// ѭ������
    {
        
        system("CLS");//����

        //��ӡ���ܲ˵�
        PrintMenu();
        printf("\t\t\t\t��������Ҫִ�еĲ���:");
        char choice;
        scanf("%c",&choice);
        getchar();// ������������

        switch (choice)
        {
        case '1': //1¼��ѧ����Ϣ
            InputStudents();
            head = Creat();
            break;

        case '2': //2��ѯѧ����Ϣ
            int searchChoice;
            printf("\t\t\t\t1.��������ѯ  2.��ѧ�Ų�ѯ  3.���γ̲�ѯ\n");
            printf("\t\t\t\t�����4.��ѧ�Ų�ѯ  5.��������ѯ  6.���γ̲�ѯ\n");
            printf("\t\t\t\t��ѡ����Ҫ��ѯ�ķ�ʽ:");
            
            scanf("%d",&searchChoice);
            getchar();// ������������
            if(searchChoice == 1) SearchName();//1.��������ѯ
            if(searchChoice == 2) SearchId();//2.��ѧ�Ų�ѯ
            if(searchChoice == 3) SearchCourse();//�γ�
            if(searchChoice == 4) SearchByList(head);//���� �����ѯ
            if(searchChoice == 5) SearchByListB(head);
            if(searchChoice == 6) SearchByListC(head);
            break;

        case '3': //3��ʾѧ����Ϣ
            PrintInfor();
            break;

        case '4': //4ɾ��ѧ����Ϣ
            DeleteStudent();
            head = Creat();
            break;

        case '5': //5�޸�ѧ����Ϣ
            ModifyStudent();
            head = Creat();
            
            break;
        
        case '6':// 6��Ϣ��ͳ��
            handle();
            break;
        case '7':// ����ѧ����Ϣ
            Insert();
            break;
        case '8':// ������д���ļ�
        
            PrintToFiles();
            break;

        case '0': //�˳�����ϵͳ
            printf("��ӭ�ٴ�ʹ�ã�\n");
            return 0;
            break;
        
        default: //���������ַ�ʱ����
            system("ClS");
            printf("\t\t\t\t!!!�������ѡ���д���������ѡ���� !!!\n");
            break;
        }

    system("PAUSE");
    }
    
    return 0;
}

// �˵�
void PrintMenu(void){
    
    system("CLS");

    printf("\t\t\t\t=================================================  �༶����:%d\n",stuNum);
    printf("\t\t\t\t===============��ӭʹ��ѧ������ϵͳ==============\n ");
    printf("\t\t\t\t=================================================\n");
    printf("\t\t\t\t=================��ѡ���Ӧ����==================\n");
    printf("\t\t\t\t=================================================\n");
    printf("\t\t\t\t=\t\t1�� ¼��ѧ����Ϣ\t\t=\n");
    printf("\t\t\t\t=\t\t2�� ��ѯѧ����Ϣ\t\t=\n");
    printf("\t\t\t\t=\t\t3�� ��ʾѧ����Ϣ\t\t=\n");
    printf("\t\t\t\t=\t\t4�� ɾ��ѧ����Ϣ\t\t=\n");
    printf("\t\t\t\t=\t\t5�� �޸�ѧ����Ϣ\t\t=\n");
    printf("\t\t\t\t=\t\t6�� ͳ��ѧ����Ϣ\t\t=\n");
    printf("\t\t\t\t=\t\t7�� ����ѧ����Ϣ\t\t=\n");
    printf("\t\t\t\t=\t\t8�� ����д���ļ�\t\t=\n");

    printf("\t\t\t\t=\t\t0�� �˳�����ϵͳ\t\t=\n");
    printf("\t\t\t\t=================================================\n");
    return ;
}

// ��Ϣ��¼��
// ¼��ѧ����Ϣ
void InputStudents(){

    int i;
    int j;
    
    

    //��ȡ��ǰʱ��
    

    for(i = 0;i<60; i++) flagId[i] = 0;//��ʼ����־����
    Student *head, *node, *end;
    node = (Student*)malloc(sizeof(struct aStudent));


    
    


    printf("\t\t\t\t������ѧ������:");        
    scanf("%d", &stuNum);
    if(stuNum > 60) {printf("\t\t\t\t����̫����,�Ҵ���������OnO!");return;}
    if(stuNum < 0) {printf("\t\t\t\t��ô���и�����!OnO!");return;}
    getchar();// ��������
    
    
    for (i = 0; i < stuNum; i++) {
        // ѧ����Ϣ������
        printf("\t\t\t\t�������%d��ѧ��������:",i+1);
        gets(stu[i].name);
        
        printf("\t\t\t\t�������%d��ѧ����ѧ��:",i+1);
        scanf("%d",&stu[i].id);
        
        getchar();// ��������

        if(flagId[stu[i].id-1] == 1){printf("\t\t\t\tѧ����ô�ظ���OnO!");return;}

        flagId[stu[i].id-1]=1;
       
        
        stu[i].totalSPoint = 0;// ��ʼ��

        // ѧ���γ���Ϣ������
        for (j = 0; j < TOTALCOURSE; j++) {
            strcpy(stu[i].course[j].courseName , courseInfor[j].courseName);
            printf("\t\t\t\t%s",courseInfor[j].courseName);
            printf("\t������ѧ���ĳɼ�:",j+1);
            scanf("%lf",&stu[i].course[j].courseScore);
            getchar();// ��������

            courseInfor[j].courseTotalScore += stu[i].course[j].courseScore;
            courseInfor[j].courseAveScore = courseInfor[j].courseTotalScore /stuNum;//�γ�ƽ���ֵļ���

            stu[i].totalScore += stu[i].course[j].courseScore;//ѧ�����ܷ�
            

            if(stu[i].course[j].courseScore >= 60) { 
            stu[i].totalPoint += (courseInfor[j].coursePoint * (stu[i].course[j].courseScore/10 - 5));// �ܼ���
            stu[i].totalSPoint += courseInfor[j].coursePoint;//�ۼ�ѧ��ȡ�õ�ѧ��
            }

            if (stu[i].course[j].courseScore == 100) courseInfor[j].rank[4]++;
            else if (stu[i].course[j].courseScore >= 85) courseInfor[j].rank[3]++;
            else if (stu[i].course[j].courseScore >= 70) courseInfor[j].rank[2]++;
            else if (stu[i].course[j].courseScore >= 60) courseInfor[j].rank[1]++;
            else {courseInfor[j].rank[0]++;
            stu[i].totalPoint += (courseInfor[j].coursePoint * 1);// �ܼ���
            }
        }





        stu[i].avePoint = stu[i].totalPoint/totalPoint;//GPA
        stu[i].aveScore = stu[i].totalScore / TOTALCOURSE;//ѧ����ƽ����
    }
    

}

// ��Ϣ�Ĳ�ѯ
// ��������ѯѧ����Ϣ
void SearchName(){
    int i;
    int j;
    char name[20];
    printf("\t\t\t\t��������Ҫ��ѯ��ѧ������:");
    gets(name);

    for(i = 0; i < stuNum; i++) {
        if(!strcmp(name,stu[i].name)) {

            printf("\t\t\t\t����:%s  ",stu[i].name);
            printf("ѧ��:%d  ",stu[i].id);
            printf("ƽ����:%.2f  ",stu[i].aveScore);
            printf("ƽ������:%.2f\n\t\t\t\t",stu[i].avePoint);
            for (j = 0; j < TOTALCOURSE; j++) {
                printf("%s:%.2f  ",stu[i].course[j].courseName,stu[i].course[j].courseScore);
            }
        }
    }

}

// ��ѧ�Ų�ѯѧ����Ϣ
void SearchId(){
    int i;
    int j;
    int id;
    int flag = 1;
    printf("\t\t\t\t��������Ҫ��ѯ��ѧ��ѧ��:");
    scanf("%d",&id);
    getchar();// ��������

    for(i = 0; i < stuNum; i++) {
        if(id == stu[i].id) {
            
            flag--;
            printf("\t\t\t\t����:%s  ",stu[i].name);
            printf("ѧ��:%d  ",stu[i].id);
            printf("ƽ����:%.2f  ",stu[i].aveScore);
            printf("ƽ������:%.2f\n\t\t\t\t",stu[i].avePoint);
            for (j = 0; j < TOTALCOURSE; j++) {
                printf("%s:%.2f  ",stu[i].course[j].courseName,stu[i].course[j].courseScore);
            }
        }
        
    }
    if(flag)printf("\t\t\t\tδ�ҵ�ƥ������");


}

// ���γ̲�ѯѧ����Ϣ
void SearchCourse(){
    int i;
    int j;
    char course[20];
    printf("\t\t\t\t��������Ҫ��ѯ�Ŀγ�:");
    gets(course);

    for(j = 0; j < TOTALCOURSE; j++) {
        if(!strcmp(course,courseInfor[j].courseName)) {
            for (i = 0; i < stuNum; i++) {
                printf("\t\t\t\t����:%s  ",stu[i].name);
                printf("ѧ��:%d  ",stu[i].id);
                printf("����:%.2f\n  ",stu[i].course[j].courseScore);
                

            
            }
            
            
        }
    }
}

// ��Ϣ��ɾ��
// ɾ��ѧ����Ϣ
void DeleteStudent() {
    int flag = 1;
    int i;
    int j;
    char name[20];
    int id;
    printf("\t\t\t\t��������Ҫɾ����ѧ��������:");
    gets(name);
    printf("\t\t\t\t��������Ҫɾ����ѧ����ѧ��:");
    scanf("%d",&id);
    getchar();
    

    for(i = 0; i < stuNum; i++) {
        if(!strcmp(name,stu[i].name) && id == stu[i].id && flag){//����ҵ�ƥ���ѧ��
            

            //��ɾ������Ŀγ��ܷ�,ƽ����,���ȼ������ı仯
            for(j = 0; j < TOTALCOURSE; j++) {
            courseInfor[j].courseTotalScore -= stu[i].course[j].courseScore;
            if (stu[i].course[j].courseScore == 100) courseInfor[j].rank[4]--;
            else if (stu[i].course[j].courseScore >= 85) courseInfor[j].rank[3]--;
            else if (stu[i].course[j].courseScore >= 70) courseInfor[j].rank[2]--;
            else if (stu[i].course[j].courseScore >= 60) courseInfor[j].rank[1]--;
            else courseInfor[j].rank[0]--;
            }
            courseInfor[j].courseAveScore = courseInfor[j].courseTotalScore /stuNum;

            //ɾ�����µ�ѧ���ṹ������ı仯
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

    if(flag) {printf("\t\t\t\tδ�ҵ�ƥ�������!");}
}

// ��Ϣ���޸�
// �޸�ѧ����Ϣ
void ModifyStudent() {
    int i;
    int j;
    int flag = 1;
    int choice;
    int selectCourse;
    char name[20];
    int id;
    double score;

    printf("\t\t\t\t��������Ҫ�޸ĵ�ѧ��������:");
    gets(name);
    printf("\t\t\t\t��������Ҫ�޸ĵ�ѧ����ѧ��:");
    scanf("%d",&id);
    getchar();
    for(i = 0; i < stuNum; i++) {
        if(!strcmp(name,stu[i].name) && id == stu[i].id && flag){
            flag--;
            printf("\t\t\t\t1.ѧ������ 2.�γ̳ɼ� \n"); 
            printf("\t\t\t\t��������Ҫ�޸ĵ�ѧ������:");
            scanf("%d",&choice);   getchar();//��������
            switch(choice){
                case 1:
                    printf("\t\t\t\t%s�������޸�Ϊ:",stu[i].name);
                    gets(name);
                    strcpy(stu[i].name,name);
                    break;
                case 2:
                {
                    for(j = 0; j < TOTALCOURSE; j++)  printf("\t\t\t\t%d.%s\n",j+1,stu[i].course[j].courseName);
                    printf("\t\t\t\t��Ҫ�޸ĵĿγ���:");
                    scanf("%d",&selectCourse);   getchar();//��������
                    
                    printf("\t\t\t\t%s�ĳɼ��� %.2f �޸�Ϊ:",
                    stu[i].course[selectCourse-1].courseName,stu[i].course[selectCourse-1].courseScore);
                    scanf("%lf",&score);   getchar();//��������

                    //���޸�����Ŀγ���Ϣ�仯
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
    if(flag) {printf("\t\t\t\tδ�ҵ�ƥ�������!");}

}

//��Ϣ�Ĵ���
//���ɼ�����
void ScoreSort(){
    int selectSort;
    char couName[20];
    int j;
    //ѡ��������ʽ
    printf("\t\t\t\t1.���Ƴɼ�����(�ݼ�)\t");
    printf("2.�ܳɼ�����(�ݼ�)\t");
    printf("3.��ѧ������\n");
    printf("\t\t\t\t��������Ҫ��������ʽ:");
    scanf("%d",&selectSort);     //ѡ��������ʽ
    getchar();//�������
    if (selectSort == 1) {
        printf("\t\t\t\t������Ҫ�����Ŀγ�����:");
        gets(couName);
        for (j = 0; j < TOTALCOURSE; j++) {
            if (strcmp(couName, courseInfor[j].courseName) == 0)
                break;
                BubleSortCourseScore(j);
        }
    
    }
    else if (selectSort == 2) BubleSortScore();
    else if(selectSort == 3 ) BubleSortId();
    else printf("\t\t\t\t�������");
        

}
//��GPA����
void GpaSort(){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//�Ƿ�������
        for(j = stuNum-1; j > i;j--){
            if(stu[j].avePoint > stu[j-1].avePoint){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;

    }
}

//ð�������ܷ�
void BubleSortScore(){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//�Ƿ�������
        for(j = stuNum-1; j > i;j--){
            if(stu[j].totalScore > stu[j-1].totalScore){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;

    }

}

//ð�������ſγ̷���
void BubleSortCourseScore(int courseid){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//�Ƿ�������
        for(j = stuNum-1; j > i;j--){
            if(stu[j].course[courseid].courseScore > stu[j-1].course[courseid].courseScore){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;
    }
}
//��ѧ������
void BubleSortId(){
    int flag;
    int i;
    int j;

    for (i = 0; i < stuNum-1; i++) {
        flag = 0;//�Ƿ�������
        for(j = stuNum-1; j > i;j--){
            if(stu[j].id < stu[j-1].id){
                flag = 1;
                Swap(j);
            }
        }
        if (flag == 0)  return;
    }
}

//��������ѧ���ṹ��
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

//��Ϣ�Ĳ���
void Insert() {
    int i = stuNum;
    int j;
    stuNum++;//��������1
        printf("\t\t\t\t������ѧ��������:");
        gets(stu[i].name);
        printf("\t\t\t\t������ѧ����ѧ��:");
        scanf("%d",&stu[i].id);
        getchar();// ��������

        if(flagId[stu[i].id-1] == 1){
            printf("\t\t\t\tѧ����ô�ظ���OnO!");
            stuNum--;
            return;
            }
        flagId[stu[i].id-1]=1;
        stu[i].totalSPoint = 0;// ��ʼ��

        // ѧ���γ���Ϣ������
        for (j = 0; j < TOTALCOURSE; j++) {
            strcpy(stu[i].course[j].courseName , courseInfor[j].courseName);
            printf("\t\t\t\t%s",courseInfor[j].courseName);
            printf("\t������ѧ���ĳɼ�:",j+1);
            scanf("%lf",&stu[i].course[j].courseScore);
            getchar();// ��������

            courseInfor[j].courseTotalScore += stu[i].course[j].courseScore;
            courseInfor[j].courseAveScore = courseInfor[j].courseTotalScore /stuNum;//�γ�ƽ���ֵļ���

            stu[i].totalScore += stu[i].course[j].courseScore;//ѧ�����ܷ�
            

            if(stu[i].course[j].courseScore >= 60) { 
            stu[i].totalPoint += (courseInfor[j].coursePoint * (stu[i].course[j].courseScore/10 - 5));// �ܼ���
            stu[i].totalSPoint += courseInfor[j].coursePoint;//�ۼ�ѧ��ȡ�õ�ѧ��
            }

            if (stu[i].course[j].courseScore == 100) courseInfor[j].rank[4]++;
            else if (stu[i].course[j].courseScore >= 85) courseInfor[j].rank[3]++;
            else if (stu[i].course[j].courseScore >= 70) courseInfor[j].rank[2]++;
            else if (stu[i].course[j].courseScore >= 60) courseInfor[j].rank[1]++;
            else {courseInfor[j].rank[0]++;
            stu[i].totalPoint += (courseInfor[j].coursePoint * 1);// �ܼ���
            }
        }
        stu[i].avePoint = stu[i].totalPoint/totalPoint;//GPA
        stu[i].aveScore = stu[i].totalScore / TOTALCOURSE;//ѧ����ƽ����
    

}


//��Ϣ����ʾ
//��ӡѧ����Ϣ
void PrintInfor(){
    int i;
    int j;
    int flag = 0;
    int failFlag=0;
    for (i = 0; i < stuNum; i++) {
        printf("\t\t\t\tѧ��:%d  ����:%s  ƽ����:%.2f  GPA:%.2f\n\t\t\t\t",stu[i].id,stu[i].name,stu[i].aveScore,stu[i].avePoint);
        for(j = 0; j < TOTALCOURSE; j++) {
            printf("%s:%.2f  ",stu[i].course[j].courseName,stu[i].course[j].courseScore);
            if(stu[i].course[j].courseScore < 60) {
                flag = 1;
                stu[i].course[j].courseScore;
                failFlag++;
            }
            
        }
        if(flag == 1) printf("\n\t\t\t\t�ҿ�����:%d\n",failFlag);
        failFlag=0;
        printf("\n");
    }
}

//д���ļ�
void PrintToFiles() {
    FILE *fb;
    FILE *cfb;
    int i = 0; 
    int j;
    
    if ((fb = fopen("G:\\Cou Des of Pro\\studentfiles.txt", "w")) == NULL) {
        printf("���ļ�: studentfiles.txt ʧ��!!!\n");
        exit(0);        //exit(0)��ʾ�������г����˳�
    }

    fprintf(fb, "ȫ��ѧ����Ϣ:\n");
    fprintf(fb, "---ѧ��-------����-");
    for (j = 0;j < TOTALCOURSE;j++) {fprintf(fb,"-----");fprintf(fb,"%s",courseInfor[j].courseName);}
    fprintf(fb, "-------ƽ����-----GPA----");
    fprintf(fb, "\n");

    while (i < stuNum) {//���ѧ����Ϣ
        fprintf(fb, "%8d", stu[i].id);
        fprintf(fb, "%15s", stu[i].name);
        for (j = 0;j < TOTALCOURSE;j++) {
            fprintf(fb, "%20.2f", stu[i].course[j].courseScore);
        }
        fprintf(fb, "%20.2f", stu[i].aveScore);
        fprintf(fb, "%12.2f", stu[i].avePoint);
        i++;
        fprintf(fb, "\n");

    }                //���ѧ����Ϣ

    fclose(fb);

    if ((cfb = fopen("G:\\Cou Des of Pro\\coursefiles.txt", "w")) == NULL) {
        fprintf(cfb,"���ļ�: coursefiles.txt ʧ��!!!\n");
        exit(0);        //exit(0)��ʾ�������г����˳�
    }
    fprintf(cfb, "\t  \tƽ����-----������-----�ҿ���\n");
    
    
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
//ͳ����Ϣ
void handle(){
    int choice;
    int selectcourse;
    int j;
    printf("\t\t\t\t1.����  2.�γ�����  \n");
    printf("\t\t\t\t��Ҫ���еĲ�����:");
    scanf("%d",&choice); getchar();
    if(choice == 1)  ScoreSort();
    else if (choice == 2){
        printf("\t\t\t\t");
        for(j=0; j < TOTALCOURSE; j++) printf("%d.%s",j+1,courseInfor[j].courseName);
        printf("\n\t\t\t\t��Ҫ�鿴�Ŀγ���:");
        scanf("%d",&selectcourse); getchar();
        if(selectcourse >3) { printf("\t\t\t\t�������!!!");    return;}
        
        printf("\t\t\t\t%s",courseInfor[selectcourse-1].courseName);
        printf("  ƽ����:%.2f",courseInfor[selectcourse-1].courseAveScore);
        printf("  ������:%.2f%%",courseInfor[selectcourse-1].rank[4]/(float)stuNum * 100);
        printf("  ��������:%.2f%%\n",courseInfor[selectcourse-1].rank[0]/(float)stuNum * 100);
    }
   else printf("\t\t\t\t�������");
}

//������غ���
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

//����Ĳ�ѯ
//ѧ��
void SearchByList(Student *head){
    Student *node=NULL;
    int id;
    int flag=1;
    printf("\t\t\t\t����������ѧ��:");
    scanf("%d",&id);  getchar();
    node = head;
    if(head !=NULL){
        do{
            if(node->id == id){
                printf("\t\t\t\tѧ��:%d  ����:%s",node->id,node->name);
                printf("  C���Գ������:%.2f",node->course[0].courseScore);
                printf("  �ߵ���ѧ:%.2f",node->course[1].courseScore);
                printf("  ���ݽṹ:%.2f",node->course[2].courseScore);
                printf("  ƽ����:%.2f\n",node->aveScore);

                flag=0;
            }
            node=node->next;

        }while(node!= NULL);

    }
    if(flag)printf("\t\t\t\tδ�ҵ�ƥ������");
}
//����
void SearchByListB(Student *head){
    Student *node=NULL;
    char name[20];
    int flag=1;
    printf("\t\t\t\t��������������:");
    scanf("%s",&name); 
    node = head;
    if(head !=NULL){
        do{
            if(!strcmp(name,node->name)){
                printf("\t\t\t\tѧ��:%d  ����:%s",node->id,node->name);
                printf("  C���Գ������:%.2f",node->course[0].courseScore);
                printf("  �ߵ���ѧ:%.2f",node->course[1].courseScore);
                printf("  ���ݽṹ:%.2f",node->course[2].courseScore);
                printf("  ƽ����:%.2f\n",node->aveScore);

                flag=0;
            }
            node=node->next;

        }while(node!= NULL);

    }
    if(flag)printf("\t\t\t\tδ�ҵ�ƥ������");
}
//�γ�
void SearchByListC(Student *head){
    Student *node=NULL;
    int course;
    int flag=1;
    printf("\t\t\t\t0.C���Գ������  1.�ߵ���ѧ  2.���ݽṹ\n");
    printf("\t\t\t\t������γ�:");
    scanf("%d",&course); getchar(); 
    node = head;
    if(head !=NULL){
        do{
            
                printf("\t\t\t\tѧ��:%d  ����:%s",node->id,node->name);
                if (course == 0)  printf("  C���Գ������:%.2f",node->course[0].courseScore);
                if (course == 1) printf("  �ߵ���ѧ:%.2f",node->course[1].courseScore);
                if (course == 2) printf("  ���ݽṹ:%.2f",node->course[2].courseScore);
                 printf("  ƽ����:%.2f\n",node->aveScore);

                flag=0;
            
            node=node->next;

        }while(node!= NULL);

    }
    if(flag)printf("\t\t\t\tδ�ҵ�ƥ������");
}

