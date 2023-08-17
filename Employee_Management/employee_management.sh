#!/bin/bash

menu () {
  echo "Menu"
  echo "1. Create Employee Record"
  echo "2. Delete Employee Record"
  echo "3. Search Employee Record"
  echo "4. Display Employee Details"
  echo "5. Sort Records"
  echo "6. List All Records"
  echo "7. Exit"
  echo 
}

create () {
	read -p "Enter Employee Name: " name
 	read -p "Enter Employee Number: " emp_number
	read -p "Enter Mobile Number: " mobile
	echo "$name $emp_number $mobile" >> employee_record.txt
	echo
	echo "Employee Record Created Successfully"
	echo
}

delete () {
	read -p "Enter the Employee number to delete: " emp_number
	grep -v "$emp_number" employee_record.txt > temp.txt
	mv temp.txt employee_record.txt
	echo
	echo "Employee Record deleted Successfully"
	echo
}

search () {
	read -p "Enter the Employee Number to search: " emp_number
	echo
	grep "$emp_number" employee_record.txt
	echo
}

display () {
	read -p "Enter the Employee Number to search: " emp_number
	echo
        grep "$emp_number" employee_record.txt
	echo
}

sort () {
	sort -t	' ' -k2n  employee_record.txt > temp.txt
	mv temp.txt employee_record.txt
	echo
	echo "Record Sorted Successfully"
}

list_record () {
	#cat  employee_record.txt
	sed 's/ / /g' employee_record.txt
}


while [ 1 ]
do 
  menu
  read -p "Enter your choice (1-7): " choice
  
  case $choice in
	1)
	    create
	    ;;
	2) 
	    delete
	    ;;
	3)
	    search
	    ;;
	4)
	    display
	    ;;
	5)
	    sort
	    ;;
	6)
	    list_records
	    ;;
	7)
	    exit 0
	    ;; 
	*)
	    echo "Invalid choice. Please enter a valid option (1-7)."
	    ;;
  esac

  echo
done
