#include <iostream>
#include <cstring>

using namespace std;

class Employ{
private:
  char name[100];
public:
  Employ(char* name){
    strcpy(this->name, name);
  }
  void ShowYourName() const{
    cout << "name: " << name<<endl;
  }

  virtual int GetPay() const{
    return 0;
  }

  virtual void ShowSalaryInfo() const{  }
};

class PermanentWorker: public Employ{
private:
  int salary;
public:
  PermanentWorker(char* name, int money):Employ(name), salary(money){}
  int GetPay() const{
    return salary;
  }
  void ShowSalaryInfo() const{
    ShowYourName();
    cout << "salary: " << GetPay()<<endl<<endl;
  }
};

class TemporaryWorker: public Employ{
private:
  int workTime;
  int payperhour;
public:
  TemporaryWorker(char* name, int pay):Employ(name), workTime(0), payperhour(pay){}
  void Addworktime(int time){
    workTime +=time;
  }
  int GetPay() const{
    return workTime*payperhour;
  }
  void ShowSalaryInfo() const{
    ShowYourName();
    cout << "Salary: " << GetPay() << endl<< endl;
  }
};

class SalesWorker:public PermanentWorker{
private:
  int salesResult;
  double bonusRatio;
public:
  SalesWorker(char* name, int money, double ratio):PermanentWorker(name, money), salesResult(0), bonusRatio(ratio){}
  void AddSalesResult(int value){
    salesResult+=value;
  }
  int GetPay() const{
    return PermanentWorker::GetPay()+(int)(salesResult*bonusRatio);
  }
  void ShowSalaryInfo() const{
    ShowYourName();
    cout<<"Salary: " << GetPay()<<endl<<endl;
  }
};

class Employhandler{
private:
  Employ* emplist[50];
  int empNum;
public:
  Employhandler():empNum(0){}
  void AddEmploy(Employ* emp){
    emplist[empNum++]=emp;
  }
  void ShowAllsalaryInfo() const{
    for(int i=0; i<empNum; i++)
      emplist[i]->ShowSalaryInfo();
  }
  void ShowTotalSalary() const{
    int sum=0;
    for(int i=0; i<empNum; i++)
      sum+=emplist[i]->GetPay();
    cout <<"Salary sum: " << sum<< endl;
  }
  ~Employhandler(){
    for(int i =0; i<empNum; i++)
      delete emplist[i];
  }
};

int main(){
  Employhandler handler;
  handler.AddEmploy(new PermanentWorker("K", 1000));
  handler.AddEmploy(new PermanentWorker("L", 1500));

  TemporaryWorker* alba = new TemporaryWorker("Jung", 700);
  alba->Addworktime(5);
  handler.AddEmploy(alba);

  SalesWorker* seller = new SalesWorker("Hong", 1000, 0.1);
  seller->AddSalesResult(7000);
  handler.AddEmploy(seller);

  handler.ShowAllsalaryInfo();
  handler.ShowTotalSalary();
  return 0;
}
