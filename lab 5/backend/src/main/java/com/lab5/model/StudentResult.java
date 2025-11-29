package com.lab5.model;

import org.springframework.data.annotation.Id;
import org.springframework.data.mongodb.core.mapping.Document;

@Document(collection = "results")
public class StudentResult {
    @Id
    private String id;
    private String name;
    private String regNo;
    
    // Subject 1
    private double sub1MSE;
    private double sub1ESE;
    
    // Subject 2
    private double sub2MSE;
    private double sub2ESE;
    
    // Subject 3
    private double sub3MSE;
    private double sub3ESE;
    
    // Subject 4
    private double sub4MSE;
    private double sub4ESE;
    
    private double totalMarks;
    private double percentage;
    private String grade;

    // Getters and Setters
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getRegNo() {
        return regNo;
    }

    public void setRegNo(String regNo) {
        this.regNo = regNo;
    }

    public double getSub1MSE() {
        return sub1MSE;
    }

    public void setSub1MSE(double sub1MSE) {
        this.sub1MSE = sub1MSE;
    }

    public double getSub1ESE() {
        return sub1ESE;
    }

    public void setSub1ESE(double sub1ESE) {
        this.sub1ESE = sub1ESE;
    }

    public double getSub2MSE() {
        return sub2MSE;
    }

    public void setSub2MSE(double sub2MSE) {
        this.sub2MSE = sub2MSE;
    }

    public double getSub2ESE() {
        return sub2ESE;
    }

    public void setSub2ESE(double sub2ESE) {
        this.sub2ESE = sub2ESE;
    }

    public double getSub3MSE() {
        return sub3MSE;
    }

    public void setSub3MSE(double sub3MSE) {
        this.sub3MSE = sub3MSE;
    }

    public double getSub3ESE() {
        return sub3ESE;
    }

    public void setSub3ESE(double sub3ESE) {
        this.sub3ESE = sub3ESE;
    }

    public double getSub4MSE() {
        return sub4MSE;
    }

    public void setSub4MSE(double sub4MSE) {
        this.sub4MSE = sub4MSE;
    }

    public double getSub4ESE() {
        return sub4ESE;
    }

    public void setSub4ESE(double sub4ESE) {
        this.sub4ESE = sub4ESE;
    }

    public double getTotalMarks() {
        return totalMarks;
    }

    public void setTotalMarks(double totalMarks) {
        this.totalMarks = totalMarks;
    }

    public double getPercentage() {
        return percentage;
    }

    public void setPercentage(double percentage) {
        this.percentage = percentage;
    }

    public String getGrade() {
        return grade;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }
}
