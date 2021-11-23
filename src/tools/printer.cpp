#include <tools/printer.h>


const byte printer_init[] = {0x1B, 0x40};
const byte printer_test[] = {0x12, 0x54};
const byte printer_cut[] = {0x1B, 0x69};

Adafruit_Thermal printer(&Serial2); 

void INIT_PRINTER(){

    printinit("Printer");

    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);

    printer.begin();

    printdone();

}

/* Nyomtatás tesztelése */
void print_test(){

    printer.setDefault();


    printer.setFont('A');
    printer.setSize('L');
    printer.boldOn();
    printer.println("Mr.Flow");

    printer.setDefault();
    printer.println("Ollio");
    printer.println("Rev. 1");
    printer.println("Frimware v0.1");
    printer.println("2021.10.08");
    
    printer.println();
    
    printer.print("Oil: ");
    printer.print(last_meas);
    printer.print(" Liter");
    
    printer.feed(1);

    printer.setBarcodeHeight(50);
    printer.printBarcode("OLLIO", CODE39);

    printer.feed(4);

    send_printer_cmd(printer_cut, 2);

    printer.setDefault();
}



/* parancs küldése a nyomtatónak */
void send_printer_cmd(const byte command[], byte len){
    for (byte i = 0; i < len; i++)
    {
        Serial2.write(command[i]);
    }
}


bool printerHasPaper(){

}


void printBlock(){
    printer.setDefault();

    printer.println();
    printer.setFont('A');
    printer.setSize('L');
    printer.boldOn();
    printer.println("Ollio");

    printer.setDefault();
    printer.print("Machine ID: ");
    printer.println(get_id());
    printer.print("Block ID: ");
    printer.println(getNextBlockNumber());
    
    

    printer.println();

    if(meas.isGoodQuality){
        printer.println(F("Good Quality Oil"));
    }
    else{
        printer.println(F("Poor Quality Oil"));
    }
    printer.print("Probe Value: ");
    printer.print(meas.quality,2);
    printer.print("V\nOil: ");
    printer.print(meas.weight,2);
    printer.println(" Kg");
    
    printer.feed(1);

    printer.print("Block date: ");
    printer.println(dateToString(now()));

    printer.feed(1);

    printer.setBarcodeHeight(50);
    printer.printBarcode("1480001", CODABAR);

    printer.feed(4);

    send_printer_cmd(printer_cut, 2);

    printer.setDefault();
}