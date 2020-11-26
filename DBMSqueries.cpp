#include<iostream>
#include<conio.h>
#include<iomanip>
#include<fstream>
#include<stdlib.h>
#include<string.h>
using namespace std;

char files[3][25] = {"csestudents.txt","courses.txt","grades.txt"};
int c1=0,c2=0,c3=0;
struct data1{
	char *rollno[100];
	char *name[100];
	int *sorted_position[2];
}student;

struct data2{
	char *courseId[100];
	char *course_name[100];
	int *sorted_position[2];
}course;

struct data3{
	char *rollno[1000];
	char *courseId[1000];
	char *grade[1000];
	int *sorted_position[3];
}marks;

bool check(char s[]){
	int i=0;
	while(s[i]!='\0'){
		if(s[i]!=' ' && s[i]!='\t') return 1;
		i++;
	}
	return 0;
}

void Readall(){
	ifstream file(files[0]);
	char line[201];
	file.getline(line,201);
	while(file.getline(line,201)){
		int i=0,in=0;
		if(check(line) == 0) break;
		student.rollno[c1] = new char[10]; student.name[c1] = new char[51];
		while(line[i]== ' ' || line[i]=='\t')i++;
		while(in<=8){ student.rollno[c1][in] = line[i];  i++;in++; }
		student.rollno[c1][in] = '\0';in=0;
		while(line[i]== ' ' || line[i]=='\t' || line[i]==',')i++;
		while(line[i]!='\0'){ student.name[c1][in++] = line[i]; ++i; }
		student.name[c1][in] = '\0';
		c1++;
	}
	file.close();

	file.open(files[1]);
	file.getline(line,201);
	while(file.getline(line,201)){
		int i=0,in=0;
		if(check(line) == 0) break;
		while(line[i]== ' ' || line[i]=='\t')i++;
		course.courseId[c2] = new char[10];
		while(in<=6){ if(line[i]!=' ' && line[i]!='\t') course.courseId[c2][in++] = line[i]; i++; }
		course.courseId[c2][in] = '\0'; in=0;
		while(line[i]== ' ' || line[i]=='\t' || line[i]==',')i++;
		course.course_name[c2] = new char[51];
		while(line[i]!='\0'){ course.course_name[c2][in++] = line[i]; ++i; }
		course.course_name[c2][in] = '\0';
		c2++;
	}
	file.close();

	file.open(files[2]);
	file.getline(line,201);
	c3=0;
	while(file.getline(line,201)){
		int i=0,in=0;
		if(check(line) == 0) break;
		while(line[i]== ' ' || line[i]=='\t')i++;
		marks.rollno[c3] = new char[10];
		while(in<=8){ if(line[i]!=' ' && line[i]!='\t') marks.rollno[c3][in++] = line[i]; i++; }++i;
		marks.rollno[c3][in] = '\0';  in=0;
		while(line[i]== ' ' || line[i] == '\t')i++;
		marks.courseId[c3] = new char[10];
		while(line[i]!=','){  marks.courseId[c3][in++] = line[i]; ++i; }++i;
		marks.courseId[c3][in] = '\0';  in=0;
		while(line[i]== ' ' || line[i] == '\t')i++;
		marks.grade[c3] = new char[3];
		marks.grade[c3][0] = line[i]; marks.grade[c3][1] = line[i+1]; marks.grade[c3][2] = '\0';
		c3++;
	}
	file.close();
}

void mergesort(char **s,int l,int r,int* str){
	if(l==r){
		str[0]=l;
		return;
	}
	int mid = (l+r)/2;
	int *a = new int[mid-l+1],*b=new int[r-mid];
	mergesort(s,l,mid,a);
	mergesort(s,mid+1,r,b);
	for(int x=0,y=0,i=0;i<r-l+1;++i){
		if(x>=mid-l+1) str[i] = b[y++];
		else if(y>=r-mid) str[i] = a[x++];
		else if(strcmp(s[a[x]],s[b[y]]) <= 0)  str[i] = a[x++];
		else str[i] = b[y++];
	}
}

void Processall(){
	student.sorted_position[0] = new int[c1];
	mergesort(student.rollno,0,c1-1,student.sorted_position[0]);

    student.sorted_position[1] = new int[c1];
    mergesort(student.name,0,c1-1,student.sorted_position[1]);

    course.sorted_position[0] = new int[c2];
	mergesort(course.courseId,0,c2-1,course.sorted_position[0]);

    course.sorted_position[1] = new int[c2];
	mergesort(course.course_name,0,c2-1,course.sorted_position[1]);

    marks.sorted_position[0] = new int[c3];
	mergesort(marks.rollno,0,c3-1,marks.sorted_position[0]);

    marks.sorted_position[1] = new int[c3];
	mergesort(marks.courseId,0,c3-1,marks.sorted_position[1]);

    marks.sorted_position[2] = new int[c3];
	mergesort(marks.grade,0,c3-1,marks.sorted_position[2]);
}

int binarySearch(int *ar,char *s,char **ss,int sz){
	int st=-1;
	for(int jump=(sz-1);jump;jump/=2){
		while((st+jump)<sz && strcmp(ss[ar[st+jump]],s)<0) st = st+jump;
	}++st;
	if(st<sz && strcmp(s,ss[ar[st]])==0);
	else st=sz;
	return st;
}
int main(){
	Readall();
	Processall();
	char cmd[101];

	while(1){
		cout << '\n';
		cin >> cmd;
		if(cmd[0] == 'Q') break;
		else if(cmd[0] == 'C'){ system("CLS"); continue; }
		if(strcmp(cmd,"SHOW") != 0 ){
			cout << "INVALID COMMAND!!!!\n";
			continue;
		}
		cin >> cmd;
		if(strcmp(cmd,"csestudents;") == 0){
			for(int i=0;i<c1;++i)  cout << student.rollno[i] << ' ' << student.name[i] << '\n';
		}
		else if(strcmp(cmd,"courses;")==0){
			for(int i=0;i<c2;++i) cout << course.courseId[i] << ' ' << course.course_name[i] <<'\n';
		}
		else if(strcmp(cmd,"grades;")==0){
			for(int i=0;i<c3;++i) cout << marks.rollno[i] << ' ' << marks.courseId[i] << ' ' << marks.grade[i] <<'\n';
		}
		else if(strcmp(cmd,"csestudents")==0){
			cin >> cmd;
			if(strcmp(cmd,"SORTBY")==0){
				cin >> cmd;
				if(strcmp(cmd,"RollNo;")==0)
					for(int i=0;i<c1;++i)  cout << student.rollno[student.sorted_position[0][i]] << ' ' << student.name[student.sorted_position[0][i]] << '\n';
				else
					for(int i=0;i<c1;++i)  cout << student.rollno[student.sorted_position[1][i]] << ' ' << student.name[student.sorted_position[1][i]] << '\n';
			}
			else {
				cin.getline(cmd,101);
				char temp[101],cd[101];
				int i=0,in=0;
				while(cmd[i]==' ')++i;
				while(cmd[i] != '='){ temp[in++] = cmd[i]; i++; }i++; temp[in] = '\0'; in=0;
				while(cmd[i]!=';')   cd[in++] = cmd[i++];  cd[in] = '\0';
				if(strcmp(temp,"RollNo")==0){
					int idx = binarySearch(student.sorted_position[0],cd,student.rollno,c1);
					if(idx >= c1)   cout << "No Data Found\n";
					while(idx<c1 && strcmp(cd,student.rollno[student.sorted_position[0][idx]])==0){ cout << student.rollno[student.sorted_position[0][idx]] << ' ' << student.name[student.sorted_position[0][idx]] << '\n'; ++idx; }
				}
				else{
					int idx = binarySearch(student.sorted_position[1],cd,student.name,c1);
					if(idx >= c1)   cout << "No Data Found\n";
					while(idx<c1 && strcmp(cd,student.name[student.sorted_position[1][idx]])==0){ cout << student.rollno[student.sorted_position[1][idx]] << ' ' << student.name [student.sorted_position[1][idx]]<< '\n'; ++idx; }
				}
			}
		}
		else if(strcmp(cmd,"courses")==0){
			cin >> cmd;
			if(strcmp(cmd,"SORTBY")==0){
				cin >> cmd;
				if(strcmp(cmd,"CourseID;")==0)
					for(int i=0;i<c2;++i) cout << course.courseId[course.sorted_position[0][i]] << ' ' << course.course_name[course.sorted_position[0][i]] <<'\n';
				else
					for(int i=0;i<c2;++i) cout << course.courseId[course.sorted_position[1][i]] << ' ' << course.course_name[course.sorted_position[1][i]] <<'\n';
			}
			else
			{
				cin.getline(cmd,101);
				char temp[101],cd[101];
				int i=0,in=0;
				while(cmd[i]==' ')++i;
				while(cmd[i] != '='){ temp[in++] = cmd[i]; i++; }++i; temp[in] = '\0'; in=0;
				while(cmd[i]!=';')  cd[in++] = cmd[i++];  cd[in] = '\0';
				if(strcmp(temp,"CourseID")==0){
					int idx = binarySearch(course.sorted_position[0],cd,course.courseId,c2);
					if(idx >= c2)   cout << "No Data Found\n";
					while(idx<c2 && strcmp(cd,course.courseId[course.sorted_position[0][idx]])==0){ cout << course.courseId[course.sorted_position[0][idx]] << ' ' << course.course_name[course.sorted_position[0][idx]] << '\n'; ++idx; }
				}
				else{
					int idx = binarySearch(course.sorted_position[1],cd,course.course_name,c2);
					if(idx >= c2)   cout << "No Data Found\n";
					while(idx<c2 && strcmp(cd,course.course_name[course.sorted_position[1][idx]] )==0){ cout << course.courseId[course.sorted_position[1][idx]] << ' ' << course.course_name[course.sorted_position[1][idx]] << '\n'; ++idx; }
				}
			}
		}
		else if(strcmp(cmd,"grades")==0){
			cin >> cmd;
			if(strcmp(cmd,"SORTBY")==0){
				cin >> cmd;
				if(strcmp(cmd,"RollNo;")==0)
					for(int i=0;i<c3;++i) cout << marks.rollno[marks.sorted_position[0][i]] << ' ' << marks.courseId[marks.sorted_position[0][i]] << ' ' << marks.grade[marks.sorted_position[0][i]] <<'\n';
				else if(strcmp(cmd,"CourseID;")==0)
					for(int i=0;i<c3;++i) cout << marks.rollno[marks.sorted_position[1][i]] << ' ' << marks.courseId[marks.sorted_position[1][i]] << ' ' << marks.grade[marks.sorted_position[1][i]] <<'\n';
				else
					for(int i=0;i<c3;++i) cout << marks.rollno[marks.sorted_position[2][i]] << ' ' << marks.courseId[marks.sorted_position[2][i]] << ' ' << marks.grade[marks.sorted_position[2][i]] <<'\n';
			}
			else{
				cin.getline(cmd,101);
				char temp[101],cd[101];
				int i=0,in=0;
				while(cmd[i]==' ')++i;
				while(cmd[i] != '='){ temp[in++] = cmd[i]; i++;}++i; temp[in] = '\0'; in=0;
				while(cmd[i]!=';')   cd[in++] = cmd[i++];  cd[in] = '\0';
				if(strcmp(temp,"RollNo")==0){
					int idx = binarySearch(marks.sorted_position[0],cd,marks.rollno,c3);
					if(idx >= c3)   cout << "No Data Found\n";
					while(idx<c3 && strcmp(cd,marks.rollno[marks.sorted_position[0][idx]])==0){ cout << cd << ' ' <<  marks.courseId[marks.sorted_position[0][idx]] << ' ' << marks.grade[marks.sorted_position[0][idx]] << '\n'; ++idx; }
				}
				else if(strcmp(temp,"CourseID")==0){
					int idx = binarySearch(marks.sorted_position[1],cd,marks.courseId,c3-1);
					if(idx >= c3)   cout << "No Data Found\n";
					while(idx<c3 && strcmp(cd,marks.courseId[marks.sorted_position[1][idx]])==0){ cout << marks.rollno[marks.sorted_position[1][idx]] << ' ' << cd << ' ' << marks.grade[marks.sorted_position[1][idx]] << '\n'; ++idx; }
				}
				else{
					int idx = binarySearch(marks.sorted_position[2],cd,marks.grade,c3);
					if(idx >= c3)   cout << "No Data Found\n";
					while(idx<c3 && strcmp(marks.grade[marks.sorted_position[2][idx]],cd)==0){ cout << marks.rollno[marks.sorted_position[2][idx]] << ' ' << marks.courseId[marks.sorted_position[2][idx]] << ' ' << cd << '\n'; ++idx; }
				}
			}
		}
		else{
			char temp[101];
			int i=0,in=0;
			while(cmd[i] != '=')++i;++i;
			while(cmd[i]!=';'){
				temp[in++] = cmd[i++];
			} temp[in] = '\0';
			int idx = binarySearch(marks.sorted_position[1],temp,marks.courseId,c3);
			if(idx>=c3) cout << "No data found!!\n";
			while(idx<c3 && strcmp(marks.courseId[marks.sorted_position[1][idx]],temp)==0){
				int name_idx = binarySearch(student.sorted_position[0],marks.rollno[marks.sorted_position[1][idx]],student.rollno,c1);
				cout << student.name[student.sorted_position[0][name_idx]] << ' ' << marks.rollno[marks.sorted_position[1][idx]] << ' ' << marks.grade[marks.sorted_position[1][idx]] << '\n';
				++idx;
			}
		}
	}
	return 0;
}
