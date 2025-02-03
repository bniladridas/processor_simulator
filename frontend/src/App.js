import React, { useState } from 'react';
import { Container, Row, Col, Form, Button, Alert } from 'react-bootstrap';
import 'bootstrap/dist/css/bootstrap.min.css';
import axios from 'axios';

function App() {
  const [binary, setBinary] = useState('');
  const [mode, setMode] = useState('STANDARD');
  const [result, setResult] = useState(null);
  const [error, setError] = useState(null);

  const handleConvert = async () => {
    try {
      console.log('Sending request with data:', { binary, mode });
      const response = await axios({
        method: 'post',
        url: 'http://localhost:8081/convert',
        data: { binary, mode },
        headers: {
          'Content-Type': 'application/json',
          'Accept': 'application/json'
        },
        timeout: 5000  // 5 second timeout
      });
      
      console.log('Full response:', response);
      setResult(response.data.hex);
      setError(null);
    } catch (err) {
      console.error('Full error object:', err);
      
      // More detailed error logging
      if (err.response) {
        // The request was made and the server responded with a status code
        // that falls out of the range of 2xx
        console.error('Error response data:', err.response.data);
        console.error('Error response status:', err.response.status);
        console.error('Error response headers:', err.response.headers);
        setError(`Server responded with error: ${err.response.status}`);
      } else if (err.request) {
        // The request was made but no response was received
        console.error('No response received:', err.request);
        setError('No response from server. Is the server running?');
      } else {
        // Something happened in setting up the request that triggered an Error
        console.error('Error setting up request:', err.message);
        setError(`Request setup error: ${err.message}`);
      }
      
      setResult(null);
    }
  };

  return (
    <Container className="mt-5">
      <h1 className="text-center mb-4">Processor Simulator</h1>
      <Row className="justify-content-md-center">
        <Col md={6}>
          <Form>
            <Form.Group>
              <Form.Label>Binary Input</Form.Label>
              <Form.Control 
                type="text" 
                placeholder="Enter binary number" 
                value={binary}
                onChange={(e) => setBinary(e.target.value)}
              />
            </Form.Group>

            <Form.Group className="mt-3">
              <Form.Label>Conversion Mode</Form.Label>
              <Form.Select 
                value={mode}
                onChange={(e) => setMode(e.target.value)}
              >
                <option value="STANDARD">Standard</option>
                <option value="SIGNED">Signed</option>
                <option value="UNSIGNED">Unsigned</option>
                <option value="FLOATING_POINT">Floating Point</option>
              </Form.Select>
            </Form.Group>

            <Button 
              variant="primary" 
              className="mt-3" 
              onClick={handleConvert}
            >
              Convert
            </Button>

            {result && (
              <Alert variant="success" className="mt-3">
                Hex Result: {result}
              </Alert>
            )}

            {error && (
              <Alert variant="danger" className="mt-3">
                {error}
              </Alert>
            )}
          </Form>
        </Col>
      </Row>
    </Container>
  );
}

export default App;
