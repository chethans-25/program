class employee:
    increment =1.8
    num=0
    def increase(self):
        #self.salary=int(self.salary*employee.increment) #1.8
        self.salary=int(self.salary*self.increment) #1.2 
    '''(if self. increment is not present, it will take employee.increment)'''
        
    def __init__(self,fname,lname,salary):
        self.fname=fname
        self.lname=lname
        self.salary=salary
        self.increment=1.2
        employee.num+=1

    @classmethod
    def change_increment(cls,amount):
        cls.increment=amount

harry=employee('harry', 'potter',550)
ron= employee('ronald', 'weasly',30000)
hermione= employee('hermione', 'granger',39000)

# harry.increase()
print(harry.salary)
employee.change_increment(2)
harry.increase()
print(harry.salary)
# print(employee.num)
# print(harry.fname,ron.lname)