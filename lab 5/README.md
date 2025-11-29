# Lab 5 - Semester Result Calculator

A full-stack application with React frontend and Spring Boot + MongoDB backend to calculate semester results based on MSE (30%) and ESE (70%) marks.

## Features

- ✨ Beautiful glassmorphic UI design
- 📊 Calculate results for 4 subjects
- 💾 Store results in MongoDB Atlas
- 📈 Display all results with grades
- 🎨 Responsive design

## Tech Stack

**Frontend:**
- React + Vite
- Axios for API calls
- Glassmorphic CSS design

**Backend:**
- Spring Boot 3.1.5
- MongoDB (Atlas)
- Java 17

## Prerequisites

- Java 17 or higher
- Maven
- Node.js and npm
- MongoDB Atlas account

## Setup Instructions

### 1. Configure MongoDB

**Option A: Using Environment Variable (Recommended)**

1. Edit `backend/.env`:
   ```
   MONGODB_URI=mongodb+srv://<username>:<password>@<cluster>.mongodb.net/lab5db
   ```

2. Replace `<username>`, `<password>`, and `<cluster>` with your MongoDB Atlas credentials.

**Option B: Direct Configuration**

Edit `backend/src/main/resources/application.properties`:
```properties
spring.data.mongodb.uri=mongodb+srv://<username>:<password>@<cluster>.mongodb.net/lab5db
```

### 2. Run Backend

```bash
cd backend
mvn clean spring-boot:run
```

The backend will start on `http://localhost:8080`

> **Note**: If you get compilation errors, run `mvn clean install` first.

### 3. Run Frontend

```bash
cd frontend
npm install  # if not already installed
npm run dev
```

The frontend will start on `http://localhost:5173`

## Usage

1. Open `http://localhost:5173` in your browser
2. Fill in student details:
   - Name
   - Registration Number
   - MSE and ESE marks for 4 subjects (0-100)
3. Click "Calculate Result"
4. View the calculated results in the table below

## Grading System

- A: 90% and above
- B: 80% - 89%
- C: 70% - 79%
- D: 60% - 69%
- F: Below 60%

## API Endpoints

- `POST /api/results` - Save and calculate result
- `GET /api/results` - Get all results

## Project Structure

```
lab 5/
├── backend/
│   ├── src/
│   │   └── main/
│   │       ├── java/com/lab5/
│   │       │   ├── Lab5Application.java
│   │       │   ├── controller/ResultController.java
│   │       │   ├── model/StudentResult.java
│   │       │   └── repository/ResultRepository.java
│   │       └── resources/
│   │           └── application.properties
│   └── pom.xml
└── frontend/
    ├── src/
    │   ├── App.jsx
    │   ├── App.css
    │   └── index.css
    └── package.json
```
