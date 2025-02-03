import React, { useState } from 'react';
import { Container, Row, Col, Form, Button, Alert, Card, Tabs, Tab, InputGroup, Table } from 'react-bootstrap';
import 'bootstrap/dist/css/bootstrap.min.css';
import { FaIndustry, FaCogs, FaInfo, FaCopy } from 'react-icons/fa';

// Conversion utility functions
const convertBinaryToDecimal = (binary) => {
  return parseInt(binary, 2);
};

const convertBinaryToHex = (binary) => {
  const decimal = convertBinaryToDecimal(binary);
  return decimal.toString(16).toUpperCase();
};

const convertBinaryToSignedDecimal = (binary) => {
  // Two's complement for signed representation
  if (binary[0] === '1') {
    // Negative number
    const invertedBinary = binary.split('').map(bit => bit === '0' ? '1' : '0').join('');
    return -1 * (parseInt(invertedBinary, 2) + 1);
  }
  return convertBinaryToDecimal(binary);
};

const convertBinaryToFloat = (binary) => {
  // Simplified floating-point conversion
  if (binary.length < 32) return 'Invalid length';
  
  const sign = binary[0] === '0' ? 1 : -1;
  const exponent = parseInt(binary.slice(1, 9), 2) - 127;
  const mantissa = binary.slice(9);
  
  let fraction = 1;
  for (let i = 0; i < mantissa.length; i++) {
    if (mantissa[i] === '1') {
      fraction += Math.pow(2, -(i + 1));
    }
  }
  
  return sign * fraction * Math.pow(2, exponent);
};

function App() {
  const [binary, setBinary] = useState('');
  const [mode, setMode] = useState('STANDARD');
  const [conversionTable, setConversionTable] = useState(null);
  const [error, setError] = useState(null);
  const [activeTab, setActiveTab] = useState('conversion');

  const handleConvert = () => {
    try {
      // Input validation
      if (!/^[01]+$/.test(binary)) {
        throw new Error('Invalid binary input. Use only 0 and 1.');
      }

      let conversionResult;
      switch(mode) {
        case 'SIGNED':
          conversionResult = {
            decimal: convertBinaryToSignedDecimal(binary).toString(),
            hex: convertBinaryToHex(binary),
            binary: binary
          };
          break;
        case 'FLOAT':
          conversionResult = {
            decimal: convertBinaryToFloat(binary.padStart(32, '0')).toString(),
            hex: convertBinaryToHex(binary),
            binary: binary
          };
          break;
        default: // STANDARD
          conversionResult = {
            decimal: convertBinaryToDecimal(binary).toString(),
            hex: convertBinaryToHex(binary),
            binary: binary
          };
      }
      
      // Generate conversion table
      const table = [
        { label: 'Binary', value: binary },
        { label: 'Decimal', value: conversionResult.decimal },
        { label: 'Hexadecimal', value: conversionResult.hex }
      ];
      setConversionTable(table);
      
      setError(null);
    } catch (err) {
      setError(err.message);
      setConversionTable(null);
    }
  };

  const copyToClipboard = (text) => {
    navigator.clipboard.writeText(text).then(() => {
      alert(`Copied: ${text}`);
    }).catch(err => {
      console.error('Failed to copy: ', err);
    });
  };

  return (
    <Container fluid className="p-4 bg-light">
      <Card className="shadow-sm">
        <Card.Header className="bg-primary text-white d-flex align-items-center">
          <FaIndustry className="me-2" /> Industrial Binary Processor Simulator
        </Card.Header>
        <Card.Body>
          <Tabs 
            activeKey={activeTab} 
            onSelect={(k) => setActiveTab(k)}
            className="mb-3"
          >
            <Tab eventKey="conversion" title={<><FaCogs /> Conversion</>}>
              <Row>
                <Col md={6}>
                  <Form.Group className="mb-3">
                    <Form.Label>Binary Input</Form.Label>
                    <InputGroup>
                      <Form.Control 
                        type="text" 
                        placeholder="Enter binary number (e.g., 1010)" 
                        value={binary}
                        onChange={(e) => setBinary(e.target.value)}
                      />
                      <Button variant="outline-secondary" onClick={() => setBinary('')}>
                        Clear
                      </Button>
                    </InputGroup>
                  </Form.Group>
                  
                  <Form.Group className="mb-3">
                    <Form.Label>Conversion Mode</Form.Label>
                    <Form.Select 
                      value={mode} 
                      onChange={(e) => setMode(e.target.value)}
                    >
                      <option value="STANDARD">Standard (Unsigned)</option>
                      <option value="SIGNED">Signed Integer</option>
                      <option value="FLOAT">Floating Point</option>
                    </Form.Select>
                  </Form.Group>
                  
                  <Button 
                    variant="primary" 
                    onClick={handleConvert}
                    disabled={!binary}
                  >
                    Convert
                  </Button>
                </Col>
                
                <Col md={6}>
                  {error && (
                    <Alert variant="danger">
                      {error}
                    </Alert>
                  )}
                  
                  {conversionTable && (
                    <Table striped bordered hover>
                      <thead>
                        <tr>
                          <th>Type</th>
                          <th>Value</th>
                          <th>Action</th>
                        </tr>
                      </thead>
                      <tbody>
                        {conversionTable.map((row, index) => (
                          <tr key={index}>
                            <td>{row.label}</td>
                            <td>{row.value}</td>
                            <td>
                              <Button 
                                variant="outline-secondary" 
                                size="sm"
                                onClick={() => copyToClipboard(row.value)}
                              >
                                <FaCopy />
                              </Button>
                            </td>
                          </tr>
                        ))}
                      </tbody>
                    </Table>
                  )}
                </Col>
              </Row>
            </Tab>
            
            <Tab eventKey="about" title={<><FaInfo /> About</>}>
              <Card.Text>
                <h4>Industrial Binary Processor Simulator</h4>
                <p>
                  A powerful tool for binary number conversions in industrial and 
                  manufacturing applications. Supports standard, signed integer, 
                  and floating-point conversions.
                </p>
                <h5>Features:</h5>
                <ul>
                  <li>Unsigned Binary Conversion</li>
                  <li>Signed Integer Representation</li>
                  <li>IEEE 754 Floating Point Conversion</li>
                  <li>Easy Copy-to-Clipboard Functionality</li>
                </ul>
              </Card.Text>
            </Tab>
          </Tabs>
        </Card.Body>
      </Card>
    </Container>
  );
}

export default App;
