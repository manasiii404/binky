package com.lab5.controller;

import com.lab5.model.StudentResult;
import com.lab5.service.ResultService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/api/results")
@CrossOrigin(origins = "http://localhost:5173") // Allow React Frontend
public class ResultController {

    @Autowired
    private ResultService service;

    @PostMapping
    public StudentResult saveResult(@RequestBody StudentResult result) {
        // Calculate Total (30% MSE + 70% ESE)
        double sub1 = (result.getSub1MSE() * 0.3) + (result.getSub1ESE() * 0.7);
        double sub2 = (result.getSub2MSE() * 0.3) + (result.getSub2ESE() * 0.7);
        double sub3 = (result.getSub3MSE() * 0.3) + (result.getSub3ESE() * 0.7);
        double sub4 = (result.getSub4MSE() * 0.3) + (result.getSub4ESE() * 0.7);
        
        result.setTotalMarks(sub1 + sub2 + sub3 + sub4);
        result.setPercentage(result.getTotalMarks() / 4);
        
        if (result.getPercentage() >= 90) result.setGrade("A");
        else if (result.getPercentage() >= 80) result.setGrade("B");
        else if (result.getPercentage() >= 70) result.setGrade("C");
        else if (result.getPercentage() >= 60) result.setGrade("D");
        else result.setGrade("F");
        
        return service.save(result);
    }

    @GetMapping
    public List<StudentResult> getAllResults() {
        return service.findAll();
    }
}
