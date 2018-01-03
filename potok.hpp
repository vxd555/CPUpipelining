#ifndef __POTOK__
#define __POTOK__

    #include <iostream>
    #include <vector>

    //#define WORD_SIZE 64 //bit | zamiast tego struct instruction{};
    #define IF_PC_SIZE 8
    //#define IF_REGISTER_SIZE 16 <- będzie z pliku wiadomo
    #define MEM_REGISTER_SIZE 16

    enum instructionType //Dzięki Maćku :)
    {
    	Rtype = 0, //instrukcje operacji może być uzywany jako zapełniacz
    	ADD = 1, //dodanie
    	MUL = 2, //mnożenie
    	SUB = 3, //odejmowanie
    	SW = 4, //zapisanie z reg -> mem
    	LW = 5, //wczytanie z mem -> reg
    	BEQ = 6, //skok warunkwy
    	NOP = 7 //nic
    };

    struct IF_ID;
    struct ID_EX;
    struct EX_MEM;
    struct MEM_WB;

    struct instruction;
    struct mux221;

    class  IF;

    struct ID_REGISTER;
    class  ID;

    class  EX;

    struct MEM_REGISTER;
    class  MEM;

    struct WB;


    struct IF_ID
    {
        int nextInstruction;
        instruction actualInstruction;

    };

    struct ID_EX
    {
        int nextInstruction,
            DataA, //ReadData1
            DataB, //ReadData2
            offset; //signed extand
    };

    struct EX_MEM
    {
        int nextInstruction, //ADD result
            isJump, //Zero
            ALUresult, //wynik z jednoski obliczeniowej
            DataB; //pobrana warto�� z drugiego rejestru
    };

    struct MEM_WB
    {
        int readedData, //dane z pamięci
        	Address; //adres obliczony przez ALU 
    };

    struct instruction
    {
        instructionType insType;
        int R1,
            R2,
            R3;
    };

    struct mux221 //multiplekser 2 do 1
    {
        int A, // returned if FALSE
            B; // returned if TRUE
        int control(int val)
        {
            return val ? B : A;
        }
    };

/***************************************** IF: Instruction fetch section *****************************************/

    class IF
    {
        int pc;
        vector<instruction> IF_REGISTER; // register in IF section
        mux221 instructionSelect; //multiplexer który wybiera czy wykonujemy skok czy nie
        IF_ID *registerIFID;
        //funkcja PC += 1;
    };

/******************************* ID: Instruction decode / register file read section *******************************/
    struct ID_REGISTER
    {
        ID_REGISTER();
        friend class ID;
    };

    class ID
    {
        ID_REGISTER* t pc;ID_REG;
        //ten odczyt i zapis zrobimy na maskach np. ReadRegister1 odczytamy tak:
        //                          0xF000 && instrukcja;
        ID_SIGN_EXTEND(/* tu przekażemy tylko te bity które są potrzebne a rozszerzenie zrobimy na przesunięciach bitowych */);

        friend class EX;
    };

/************************************ EX: Execute / address calculation section ************************************/
    class EX
    {
        //shift 2
        // v
		//add → wynik do multipleksera w IF_ADD;
        // v
        //wynik z IF_ADD

        //shift 2
        // ↓
        //multiplekser → X
        // ↑
        //readData2 z ID_REGISTER

        //ReadData1 z ID_REGISTER
        // ↓
        //ALU
        // ↑
        // X

        friend struct IF_ADD;
        friend struct ID_REGISTER;
    };

/******************************************** MEM: Memory access section ********************************************/
    struct MEM_REGISTER
    {
        MEM_REGISTER(); //konstruowanie pamięci, jej rozmiaru itd;
    };

    class MEM
    {
        MEM_REGISTER* MEM_REG;

        //ALU result z EX → this->Address
        //ReadData2 z ID_REGISTER → this->WriteData

        friend class EX;
        friend struct ID_REGISTER;
    };

/********************************************** WB: Write back section **********************************************/
    struct WB
    {
        //ReadData z MEM_REGISTER
        // ↓
        //multiplekser → WriteData z ID_REGISTER
        // ↑
        //ALU Result z EX

        friend struct MEM_REGISTER;
        friend class EX;
    };

	/*struct controlOutput //do multicycle
	{
		bool	PCwriteCond, //wzapisz gdy jest spe�niony warunek
				PCwrite, //zapisz zawsze
				IorD, //nastepna instrukcja lub skok
				MemRead,
				MemWrite,
				MemToReg, //wczytujemy albo dane z instrukcji, albo z tego co by�o na WB
				IRwrite,
				CauseWrite, //nie wiadomo po co
				IntCause,
				
	}*/

	struct controlOutput
	{
		bool	regDst,
				jump,
				breanch,
				memRead,
				memToReg,
				memWrite,
				ALUsrc,	
				regWrite;
		int		ALUop;
	};

    class RISC
    {
        IF instructionFetch;
        IF_ID registerIFID;
        ID instructionDecode;
        ID_EX registerIDEX;
        EX instructionExecute;
        EX_MEM registerEXMEM;
        MEM instructionMemory;
        MEM_WB registerMEMWB;
        WB instructionWriteBack;
        
        controlOutput opcode;


    };

#endif /* __POTOK__ */
