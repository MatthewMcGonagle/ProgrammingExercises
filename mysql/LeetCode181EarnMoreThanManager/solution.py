# Find which employees earn more than their manager.
# Table: Employee
#   Columns: Id, Name, Salary, ManagerId
# Some ManagerId are NULL

SELECT Name as Employee
FROM Employee
    INNER JOIN (
        SELECT Id, Salary as ManagerSalary
        FROM Employee) as Managers
    ON Employee.ManagerId = Managers.Id
where Salary > ManagerSalary
