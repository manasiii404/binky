package com.lab5.service;

import com.lab5.model.StudentResult;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

@Service
public class ResultService {
    private final List<StudentResult> results = new ArrayList<>();

    public StudentResult save(StudentResult result) {
        if (result.getId() == null) {
            result.setId(UUID.randomUUID().toString());
        }
        results.add(result);
        return result;
    }

    public List<StudentResult> findAll() {
        return new ArrayList<>(results);
    }
}
