
void cmdBuf(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BUFFER): " << (operands[0] = operands[1]) << std::endl;
    }
}

void cmdInhibit(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (INHIBIT): " << (operands[0] = operands[0]) << std::endl;
    }
}

void cmdEquiv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EQUIV): " << (operands[0] == operands[1]) << std::endl;
    }
}

void cmdId(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (IDENTITY): " << operands[0] << std::endl; // hceck this
    }
}

void cmdBool(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (BOOLEAN): " << (operands[0] != 0 ? "true" : "false") << std::endl;
    }

void cmdBin2Fuz(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (BINARY-2-FUZZY): " << (100 - operands[0]) << std::endl;
    }
}

void cmdFuz2Bin(double* operands, int numOperands) {
    if (numOperands >= 1) {
        std::cout << "Result (FUZZY-2-BINARY): " << (operands[0] / 2 * 0.1) << std::endl;
    }
}

void cmdVectAdd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR ADD): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdVectSub(int& result) {
    if (numOperands >= 2) {
        std::cout << "Result (VECTOR SUB): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdDotProd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DOT  PRODUCT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxDet(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MATRIX DET): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxInv(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MATRIX INV): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd3x3Det(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (3X3 DET): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMtrxAnd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MATRIX AND): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (BREAK): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (END): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (EXIT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PROMPT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (DONE): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmd(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdHttp(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (HTTP): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdProxy(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PROXY): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdHttp(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (HTTP): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdGetProxy(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (GET PROXY): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdServer(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SERVER): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdUser(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (USER): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdUserAgent(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (USER AGENT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdFnct(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (FNCT): " << (operands[0] <= operands[1]) << std::endl;
    }
}


void cmdAttribute(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (ATTRIBUTE): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdType(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (TYPE): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdWait(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (WAIT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdSleep(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (SLEEP): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdPrint(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PRINT): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdCher(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (CHAR): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdRead(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (READ): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdMove(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (MOVE): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdNull(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (NULL): " << (operands[0] <= operands[1]) << std::endl;
    }
}

void cmdPath(double* operands, int numOperands) {
    if (numOperands >= 2) {
        std::cout << "Result (PATH): " << (operands[0] <= operands[1]) << std::endl;
    }
}
