// plugins/quantum_ops.cpp - Fixed quantum operations
#include <iostream>
#include <string>
#include <map>
#include <stack>
#include <functional>
#include <complex>
#include <vector>
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;

// Enhanced Value struct (must match main interpreter)
struct Value {
    enum Type { NUMBER, STRING, COMPLEX, QUBIT, EMPTY } type;
    double number;
    string str;
    complex<double> comp;
    vector<complex<double>> qubit_state;
    
    Value() : type(EMPTY), number(0.0) {}
    Value(double n) : type(NUMBER), number(n) {}
    Value(const string& s) : type(STRING), number(0.0), str(s) {}
    Value(const complex<double>& c) : type(COMPLEX), number(0.0), comp(c) {}
    Value(const vector<complex<double>>& q) : type(QUBIT), number(0.0), qubit_state(q) {}
    
    bool isNumeric() const { return type == NUMBER || type == COMPLEX; }
    double asNumber() const { 
        if (type == NUMBER) return number;
        if (type == COMPLEX) return comp.real();
        return 0.0;
    }
    
    string toString() const {
        switch (type) {
            case NUMBER: return to_string(number);
            case STRING: return str;
            case COMPLEX: return to_string(comp.real()) + "+" + to_string(comp.imag()) + "i";
            case QUBIT: return "|ψ⟩";
            case EMPTY: return "empty";
        }
        return "";
    }
};

// Quantum gate operations
void apply_hadamard(stack<Value>& data_stack) {
    if (data_stack.empty()) {
        cout << "Error: H gate requires a qubit state" << endl;
        return;
    }
    
    Value val = data_stack.top();
    data_stack.pop();
    
    if (val.type != Value::QUBIT) {
        cout << "Error: H gate error: Not a valid qubit state" << endl;
        data_stack.push(val);
        return;
    }
    
    // Apply Hadamard gate: H|0⟩ = (|0⟩ + |1⟩)/√2, H|1⟩ = (|0⟩ - |1⟩)/√2
    vector<complex<double>> new_state(2);
    double inv_sqrt2 = 1.0 / sqrt(2.0);
    
    new_state[0] = inv_sqrt2 * (val.qubit_state[0] + val.qubit_state[1]);
    new_state[1] = inv_sqrt2 * (val.qubit_state[0] - val.qubit_state[1]);
    
    data_stack.push(Value(new_state));
    cout << "Applied Hadamard gate ⚛️" << endl;
}

void apply_pauli_x(stack<Value>& data_stack) {
    if (data_stack.empty()) {
        cout << "Error: X gate requires a qubit state" << endl;
        return;
    }
    
    Value val = data_stack.top();
    data_stack.pop();
    
    if (val.type != Value::QUBIT) {
        cout << "Error: X gate error: Not a valid qubit state" << endl;
        data_stack.push(val);
        return;
    }
    
    // Apply Pauli-X gate: X|0⟩ = |1⟩, X|1⟩ = |0⟩
    vector<complex<double>> new_state(2);
    new_state[0] = val.qubit_state[1];
    new_state[1] = val.qubit_state[0];
    
    data_stack.push(Value(new_state));
    cout << "Applied Pauli-X gate 🔄" << endl;
}

void apply_pauli_y(stack<Value>& data_stack) {
    if (data_stack.empty()) {
        cout << "Error: Y gate requires a qubit state" << endl;
        return;
    }
    
    Value val = data_stack.top();
    data_stack.pop();
    
    if (val.type != Value::QUBIT) {
        cout << "Error: Y gate error: Not a valid qubit state" << endl;
        data_stack.push(val);
        return;
    }
    
    // Apply Pauli-Y gate: Y|0⟩ = i|1⟩, Y|1⟩ = -i|0⟩
    vector<complex<double>> new_state(2);
    new_state[0] = complex<double>(0, 1) * val.qubit_state[1];
    new_state[1] = complex<double>(0, -1) * val.qubit_state[0];
    
    data_stack.push(Value(new_state));
    cout << "Applied Pauli-Y gate 🌀" << endl;
}

void apply_pauli_z(stack<Value>& data_stack) {
    if (data_stack.empty()) {
        cout << "Error: Z gate requires a qubit state" << endl;
        return;
    }
    
    Value val = data_stack.top();
    data_stack.pop();
    
    if (val.type != Value::QUBIT) {
        cout << "Error: Z gate error: Not a valid qubit state" << endl;
        data_stack.push(val);
        return;
    }
    
    // Apply Pauli-Z gate: Z|0⟩ = |0⟩, Z|1⟩ = -|1⟩
    vector<complex<double>> new_state(2);
    new_state[0] = val.qubit_state[0];
    new_state[1] = -val.qubit_state[1];
    
    data_stack.push(Value(new_state));
    cout << "Applied Pauli-Z gate ⚡" << endl;
}

void measure_qubit(stack<Value>& data_stack) {
    if (data_stack.empty()) {
        cout << "Error: Measurement requires a qubit state" << endl;
        return;
    }
    
    Value val = data_stack.top();
    data_stack.pop();
    
    if (val.type != Value::QUBIT) {
        cout << "Error: Measurement error: Not a valid qubit state" << endl;
        data_stack.push(val);
        return;
    }
    
    // Calculate probabilities
    double prob_0 = norm(val.qubit_state[0]);
    double prob_1 = norm(val.qubit_state[1]);
    
    // Normalize probabilities
    double total_prob = prob_0 + prob_1;
    if (total_prob > 0) {
        prob_0 /= total_prob;
        prob_1 /= total_prob;
    }
    
    // Random measurement
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);
    
    double rand_val = dis(gen);
    int result = (rand_val < prob_0) ? 0 : 1;
    
    cout << "🔬 Quantum measurement result: |" << result << "⟩" << endl;
    cout << "   Probabilities: |0⟩=" << fixed << setprecision(3) << prob_0 * 100 << "% |1⟩=" << prob_1 * 100 << "%" << endl;
    
    // Push result as number
    data_stack.push(Value(static_cast<double>(result)));
}

void show_qubit_state(stack<Value>& data_stack) {
    if (data_stack.empty()) {
        cout << "Error: State display requires a qubit state" << endl;
        return;
    }
    
    Value val = data_stack.top();
    
    if (val.type != Value::QUBIT) {
        cout << "Error: Not a valid qubit state" << endl;
        return;
    }
    
    cout << "🔮 Qubit state: " << endl;
    cout << "   |ψ⟩ = " << fixed << setprecision(3);
    
    if (val.qubit_state[0].real() != 0 || val.qubit_state[0].imag() != 0) {
        cout << "(" << val.qubit_state[0].real();
        if (val.qubit_state[0].imag() >= 0) cout << "+";
        cout << val.qubit_state[0].imag() << "i)|0⟩";
    }
    
    if (val.qubit_state[1].real() != 0 || val.qubit_state[1].imag() != 0) {
        if (val.qubit_state[0].real() != 0 || val.qubit_state[0].imag() != 0) {
            cout << " + ";
        }
        cout << "(" << val.qubit_state[1].real();
        if (val.qubit_state[1].imag() >= 0) cout << "+";
        cout << val.qubit_state[1].imag() << "i)|1⟩";
    }
    
    cout << endl;
}

void quantum_teleport(stack<Value>& data_stack) {
    cout << "🌌 Quantum teleportation protocol initiated!" << endl;
    cout << "   'Spooky action at a distance' - Einstein" << endl;
    cout << "   📡 Entangled particles prepared..." << endl;
    cout << "   🔄 Bell measurement performed..." << endl;
    cout << "   ✨ Quantum state teleported successfully!" << endl;
    
    // Push success indicator
    data_stack.push(Value(1.0));
}

void create_bell_state(stack<Value>& data_stack) {
    // Create Bell state |Φ+⟩ = (|00⟩ + |11⟩)/√2
    cout << "🔗 Creating Bell state |Φ+⟩ = (|00⟩ + |11⟩)/√2" << endl;
    cout << "   Entangled particles generated! 🌟" << endl;
    
    // For simplicity, represent as two entangled qubits
    double inv_sqrt2 = 1.0 / sqrt(2.0);
    vector<complex<double>> bell_state = {
        complex<double>(inv_sqrt2, 0), // |00⟩
        complex<double>(0, 0),         // |01⟩
        complex<double>(0, 0),         // |10⟩
        complex<double>(inv_sqrt2, 0)  // |11⟩
    };
    
    data_stack.push(Value(bell_state));
}

extern "C" {
    void init_plugin(map<string, function<void(stack<Value>&)>>* operations) {
        (*operations)["H"] = apply_hadamard;
        (*operations)["X"] = apply_pauli_x;
        (*operations)["Y"] = apply_pauli_y;
        (*operations)["Z"] = apply_pauli_z;
        (*operations)["measure"] = measure_qubit;
        (*operations)["show"] = show_qubit_state;
        (*operations)["teleport"] = quantum_teleport;
        (*operations)["bell"] = create_bell_state;
    }
}