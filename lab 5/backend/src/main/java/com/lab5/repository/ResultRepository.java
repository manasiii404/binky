package com.lab5.repository;

import com.lab5.model.StudentResult;
import org.springframework.data.mongodb.repository.MongoRepository;

public interface ResultRepository extends MongoRepository<StudentResult, String> {
}
