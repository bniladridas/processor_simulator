import React, { useState } from 'react';
import { Container, Row, Col, Form, Button, Alert, Card, Tabs, Tab, InputGroup, Table } from 'react-bootstrap';
import 'bootstrap/dist/css/bootstrap.min.css';
import axios from 'axios';
import { FaIndustry, FaCogs, FaChartLine, FaInfo, FaCopy } from 'react-icons/fa';

function convertBinary(binary) {
  console.log('Converting binary:', binary);  // Debug log
  
  // Validate binary input
  if (!/^[01]+$/.test(binary)) {
    console.error('Invalid binary input');  // Debug log
    throw new Error('Invalid binary input');
  }

  // Unsigned interpretation
  const unsignedDecimal = parseInt(binary, 2);
  console.log('Unsigned Decimal:', unsignedDecimal);  // Debug log
  
  // Signed (Two's Complement) interpretation
  let signedDecimal;
  if (binary[0] === '1') {
    // Invert bits and add 1 for two's complement
    const invertedBits = binary.split('').map(bit => bit === '0' ? '1' : '0').join('');
    signedDecimal = -(parseInt(invertedBits, 2) + 1);
  } else {
    signedDecimal = unsignedDecimal;
  }
  console.log('Signed Decimal:', signedDecimal);  // Debug log
  
  // Floating Point (simplified approximation)
  const floatingPointApprox = binary[0] === '1' 
    ? parseFloat(`1.${binary.slice(1)}`) * Math.pow(2, binary.length - 1)
    : unsignedDecimal;
  console.log('Floating Point:', floatingPointApprox);  // Debug log

  return {
    unsigned: {
      decimal: unsignedDecimal,
      hex: `0x${unsignedDecimal.toString(16).toUpperCase()}`
    },
    signed: {
      decimal: signedDecimal,
      hex: `0x${Math.abs(signedDecimal).toString(16).toUpperCase()}`
    },
    floatingPoint: {
      decimal: floatingPointApprox.toFixed(1),
      hex: `0x${Math.round(floatingPointApprox).toString(16).toUpperCase()}`
    }
  };
}

function App() {
  const [binary, setBinary] = useState('');
  const [mode, setMode] = useState('STANDARD');
  const [result, setResult] = useState({
    hex: '',
    decimal: '',
    binary: ''
  });
  const [conversionTable, setConversionTable] = useState(null);
  const [error, setError] = useState(null);
  const [activeTab, setActiveTab] = useState('conversion');

  const handleConvert = async () => {
    try {
      console.log('Handling conversion for:', binary);  // Debug log
      
      // Input validation
      if (!/^[01]+$/.test(binary)) {
        console.error('Invalid input');  // Debug log
        throw new Error('Invalid binary input. Use only 0 and 1.');
      }

      const response = await axios({
        method: 'post',
        url: process.env.REACT_APP_BACKEND_URL || 'http://localhost:8081/convert',
        data: { binary, mode },
        headers: {
          'Content-Type': 'application/json',
          'Accept': 'application/json'
        },
        timeout: 5000
      });
      
      // Compute detailed conversions
      const conversions = convertBinary(binary);
      
      setResult({
        hex: response.data.hex,
        decimal: conversions.unsigned.decimal.toString(),
        binary: binary
      });
      setConversionTable(conversions);
      setError(null);
    } catch (err) {
      console.error('Conversion error:', err);
      setError(err.message || 'Conversion failed');
      setResult({ hex: '', decimal: '', binary: '' });
      setConversionTable(null);
    }
  };

  const copyToClipboard = (text) => {
    navigator.clipboard.writeText(text).then(() => {
      alert(`Copied ${text} to clipboard`);
    });
  };

  return (
    <Container fluid className="p-4" style={{ minHeight: '100vh' }}>
      <Card className="industrial-card shadow-lg">
        <Card.Header className="industrial-header d-flex align-items-center">
          <FaIndustry className="me-2" />
          <h2 className="mb-0">Industrial Binary Converter</h2>
        </Card.Header>
        <Card.Body>
          <Tabs 
            activeKey={activeTab}
            onSelect={(k) => setActiveTab(k)}
            className="mb-3"
          >
            <Tab eventKey="conversion" title={<><FaCogs className="me-2" />Conversion</>}>
              <Row>
                <Col md={6}>
                  <Form.Group className="mb-3">
                    <Form.Label>Binary Input</Form.Label>
                    <InputGroup>
                      <Form.Control 
                        type="text" 
                        placeholder="Enter binary number (e.g., 1011)" 
                        value={binary}
                        onChange={(e) => setBinary(e.target.value)}
                        isInvalid={!!error}
                        className="industrial-input"
                      />
                      <Button 
                        variant="outline-secondary" 
                        onClick={() => setBinary('')}
                        className="industrial-button"
                      >
                        Clear
                      </Button>
                    </InputGroup>
                    <Form.Text className="text-muted">
                      Enter a valid binary number (0s and 1s only)
                    </Form.Text>
                  </Form.Group>

                  <Form.Group className="mb-3">
                    <Form.Label>Conversion Mode</Form.Label>
                    <Form.Select 
                      value={mode}
                      onChange={(e) => setMode(e.target.value)}
                      className="industrial-input"
                    >
                      <option value="STANDARD">Standard</option>
                      <option value="SIGNED">Signed</option>
                      <option value="UNSIGNED">Unsigned</option>
                      <option value="FLOATING_POINT">Floating Point</option>
                    </Form.Select>
                  </Form.Group>

                  <Button 
                    variant="primary" 
                    onClick={handleConvert}
                    disabled={!binary}
                    className="industrial-button"
                  >
                    Convert
                  </Button>
                </Col>

                <Col md={6}>
                  {error && (
                    <Alert variant="warning" className="industrial-alert mt-3">
                      {error}
                    </Alert>
                  )}

                  {result.hex && (
                    <Card className="mt-3 industrial-card">
                      <Card.Body>
                        <h4>Conversion Results</h4>
                        <Row>
                          <Col>
                            <strong>Hexadecimal:</strong>
                            <InputGroup className="mt-2">
                              <Form.Control 
                                type="text" 
                                value={result.hex} 
                                readOnly 
                                className="industrial-input"
                              />
                              <Button 
                                variant="outline-secondary" 
                                onClick={() => copyToClipboard(result.hex)}
                                className="industrial-button"
                              >
                                <FaCopy />
                              </Button>
                            </InputGroup>
                          </Col>
                          <Col>
                            <strong>Decimal:</strong>
                            <InputGroup className="mt-2">
                              <Form.Control 
                                type="text" 
                                value={result.decimal} 
                                readOnly 
                                className="industrial-input"
                              />
                              <Button 
                                variant="outline-secondary" 
                                onClick={() => copyToClipboard(result.decimal)}
                                className="industrial-button"
                              >
                                <FaCopy />
                              </Button>
                            </InputGroup>
                          </Col>
                        </Row>
                      </Card.Body>
                    </Card>
                  )}
                </Col>
              </Row>

              {conversionTable && (
                <Row className="mt-4">
                  <Col>
                    <Card className="industrial-card">
                      <Card.Header className="industrial-header d-flex align-items-center">
                        <FaChartLine className="me-2" />
                        <h4 className="mb-0">Detailed Conversion Table</h4>
                      </Card.Header>
                      <Card.Body>
                        <Table striped bordered hover responsive className="industrial-table">
                          <thead>
                            <tr>
                              <th>Representation</th>
                              <th>Interpretation</th>
                              <th>Decimal Value</th>
                              <th>Hexadecimal</th>
                            </tr>
                          </thead>
                          <tbody>
                            <tr>
                              <td>Unsigned (Standard)</td>
                              <td>Regular binary interpretation</td>
                              <td>{conversionTable.unsigned.decimal}</td>
                              <td>{conversionTable.unsigned.hex}</td>
                            </tr>
                            <tr>
                              <td>Signed (Two's Complement)</td>
                              <td>Negative if MSB = 1</td>
                              <td>{conversionTable.signed.decimal}</td>
                              <td>{conversionTable.signed.hex}</td>
                            </tr>
                            <tr>
                              <td>Floating Point (Approx.)</td>
                              <td>IEEE 754 style approximation</td>
                              <td>{conversionTable.floatingPoint.decimal}</td>
                              <td>{conversionTable.floatingPoint.hex}</td>
                            </tr>
                          </tbody>
                        </Table>
                      </Card.Body>
                    </Card>
                  </Col>
                </Row>
              )}
            </Tab>

            <Tab eventKey="info" title={<><FaInfo className="me-2" />About</>}>
              <Card.Body>
                <h4>Industrial Binary Converter</h4>
                <p>
                  A precision engineering tool designed for industrial and 
                  manufacturing applications. Advanced binary conversion 
                  with multiple representation modes.
                </p>
                <h5>Technical Features:</h5>
                <ul>
                  <li>Precise binary to hexadecimal conversion</li>
                  <li>Multiple conversion modes</li>
                  <li>Detailed conversion table</li>
                  <li>Industrial-grade error handling</li>
                  <li>Monospaced technical typography</li>
                </ul>
              </Card.Body>
            </Tab>
          </Tabs>
        </Card.Body>
      </Card>
    </Container>
  );
}

export default App;
