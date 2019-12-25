// C343 / Summer 2018
// Lab Mini-Assignments 04
// Name: Yuheng Lin
// Username: yuhelin

import java.util.*;

public class Lab04 {
    public static void main(String[] args){
        // Task 1

        System.out.println("java.vm.version is " + System.getProperty("java.vm.version"));
        //java.vm.version is 25.162-b12

        // Task 2 testing;

        String name = "Ray";
        Student stu1 = new Student(name);
        stu1.setDepartment("CSCI");

        Student[] ListOfStu = new Student[3];
        ListOfStu[0] = stu1;
        ListOfStu[1] = new Student("Tom");
        ListOfStu[1].setDepartment("SPEA");
        ListOfStu[2] = new Student("Jason");
        ListOfStu[2].setDepartment("Kelly");
        ListOfStu[0].display();
        ListOfStu[1].display();
        ListOfStu[2].display();

    }
}
