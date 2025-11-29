import { useState, useEffect } from 'react';
import axios from 'axios';
import './App.css';

function App() {
  const [formData, setFormData] = useState({
    name: '',
    regNo: '',
    sub1MSE: '',
    sub1ESE: '',
    sub2MSE: '',
    sub2ESE: '',
    sub3MSE: '',
    sub3ESE: '',
    sub4MSE: '',
    sub4ESE: ''
  });

  const [results, setResults] = useState([]);
  const [loading, setLoading] = useState(false);

  const API_URL = 'http://localhost:8081/api/results';

  useEffect(() => {
    fetchResults();
  }, []);

  const fetchResults = async () => {
    try {
      const response = await axios.get(API_URL);
      setResults(response.data);
    } catch (error) {
      console.error('Error fetching results:', error);
    }
  };

  const handleChange = (e) => {
    setFormData({
      ...formData,
      [e.target.name]: e.target.value
    });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    setLoading(true);

    try {
      const dataToSend = {
        ...formData,
        sub1MSE: parseFloat(formData.sub1MSE),
        sub1ESE: parseFloat(formData.sub1ESE),
        sub2MSE: parseFloat(formData.sub2MSE),
        sub2ESE: parseFloat(formData.sub2ESE),
        sub3MSE: parseFloat(formData.sub3MSE),
        sub3ESE: parseFloat(formData.sub3ESE),
        sub4MSE: parseFloat(formData.sub4MSE),
        sub4ESE: parseFloat(formData.sub4ESE)
      };

      await axios.post(API_URL, dataToSend);

      // Reset form
      setFormData({
        name: '',
        regNo: '',
        sub1MSE: '',
        sub1ESE: '',
        sub2MSE: '',
        sub2ESE: '',
        sub3MSE: '',
        sub3ESE: '',
        sub4MSE: '',
        sub4ESE: ''
      });

      // Refresh results
      fetchResults();
    } catch (error) {
      console.error('Error submitting data:', error);
      alert('Error submitting data. Please check your input.');
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="app">
      <div className="container">
        <div className="glass-card">
          <h1 className="title">📊 Semester Result Calculator</h1>
          <p className="subtitle">MSE: 30% | ESE: 70%</p>

          <form onSubmit={handleSubmit} className="form">
            <div className="form-row">
              <div className="form-group">
                <label>Student Name</label>
                <input
                  type="text"
                  name="name"
                  value={formData.name}
                  onChange={handleChange}
                  required
                  placeholder="Enter name"
                />
              </div>
              <div className="form-group">
                <label>Registration No</label>
                <input
                  type="text"
                  name="regNo"
                  value={formData.regNo}
                  onChange={handleChange}
                  required
                  placeholder="Enter reg no"
                />
              </div>
            </div>

            {[1, 2, 3, 4].map((num) => (
              <div key={num} className="subject-section">
                <h3>Subject {num}</h3>
                <div className="form-row">
                  <div className="form-group">
                    <label>MSE (30%)</label>
                    <input
                      type="number"
                      name={`sub${num}MSE`}
                      value={formData[`sub${num}MSE`]}
                      onChange={handleChange}
                      required
                      min="0"
                      max="100"
                      step="0.01"
                      placeholder="0-100"
                    />
                  </div>
                  <div className="form-group">
                    <label>ESE (70%)</label>
                    <input
                      type="number"
                      name={`sub${num}ESE`}
                      value={formData[`sub${num}ESE`]}
                      onChange={handleChange}
                      required
                      min="0"
                      max="100"
                      step="0.01"
                      placeholder="0-100"
                    />
                  </div>
                </div>
              </div>
            ))}

            <button type="submit" className="submit-btn" disabled={loading}>
              {loading ? 'Calculating...' : 'Calculate Result'}
            </button>
          </form>
        </div>

        {results.length > 0 && (
          <div className="glass-card results-card">
            <h2 className="results-title">📈 Results</h2>
            <div className="table-container">
              <table className="results-table">
                <thead>
                  <tr>
                    <th>Name</th>
                    <th>Reg No</th>
                    <th>Total Marks</th>
                    <th>Percentage</th>
                    <th>Grade</th>
                  </tr>
                </thead>
                <tbody>
                  {results.map((result) => (
                    <tr key={result.id}>
                      <td>{result.name}</td>
                      <td>{result.regNo}</td>
                      <td>{result.totalMarks.toFixed(2)}</td>
                      <td>{result.percentage.toFixed(2)}%</td>
                      <td>
                        <span className={`grade grade-${result.grade}`}>
                          {result.grade}
                        </span>
                      </td>
                    </tr>
                  ))}
                </tbody>
              </table>
            </div>
          </div>
        )}
      </div>
    </div>
  );
}

export default App;
