/* 
 * File:   nRF24L01P.h
 * Author: r0rshark
 *
 * Created on 3 gennaio 2014, 17.22
 */
#include "spi_driver.h"

#ifndef NRF24L01P_H
#define	NRF24L01P_H


class nRF24L01P {
public:
    
    /**
     * Default constructor. In this the module is configured with default options
     */
    nRF24L01P();
    
    nRF24L01P(const nRF24L01P& orig);
    
    /**
     * Destructor
     */
    virtual ~nRF24L01P();    
    
    /**
     * The function powers up the module and flushes tx queue
     */
    void power_up();
    
    /**
     * The function powers down the module
     */
    void power_down();
    
    /**
     * The function sets the module into transmit mode
     */
    void set_transmit_mode();
    
    /**
     * The function sets the module into receive mode
     */
    void set_receive_mode();
    
    /**
     * The function configures the crc width
     * @param width - width of the crc. Correct Values: 0, 8 or 16
     */
    void set_crc_width(int width);
    

    /**
     * The function sets the frequency of the channel used by the module
     * @param frequency - frequency value, between 2400 and 2525
     */
    void set_frequency(int frequency);
    
    /**
     * The function sets the signal power output
     * @param power - value 0, -6, -12, -18
     */
    void set_power_output(int power);
    
    /**
     * The function sets the data rate
     * @param rate - value 250, 1000 or 2000
     */
    void set_air_data_rate(int rate);
   
    /**
     * The function sets the address field width
     * @param number - possible values 3, 4 or 5
     */
    void set_tx_num_bit(int number);
    
    /**
     * The function sets the dimension of the payload to be sent to other boards
     * @param size - dimension of the payload, value between 0 and 32
     */
    void set_transfer_size(int size);
   
    /**
     * The function returns the frequency value configured in the module
     * @return a value between 2400 and 2525 MHz
     */
    int get_frequency();
    
    /**
     * The function returns the data rate value configured in the module.
     * @return 250 if it's 250 KBPS, 1000 if it's 1 MBPS, 2000 if it's 2 MBPS
     */
    int get_air_data_rate(); 
   
    /**
     * The function returns the output power value configured in the module
     * @return   0 if it's 0 dB, -6 if it's -6 dB, -12 if it's -12 dB,, -18 if it's -18 dB
     */
    int get_output_power();
    
    /**
     * The function returns the crc width value configured in the module
     * @return 0 if CRC = 0 , 8 if CRC is 8 bits, 16 if CRC is 16 bits
     */
    int get_crc_width();
    

    /**
     * Function to get the status register
     * @return the value of the status register
     */
    int get_register_status();
    
    /**
     * The function returns the rpd bit
     * @return - rpd bit value
     */
    int get_rpd_status();
   
    /**
     * THe function resets the rx interrupt bit
     */
    void reset_interrupt();
   
    /**
     * The function checks if there are some packets in the pipe 0 of the 
     * rx module buffer.
     * @return true if there is at least one packet, otherwise false
     */
    bool packet_in_pipe0();
    
    /**
     * The function enables module to generate automatically transmission acknolegment.
     */
    void disable_auto_ack();
    
    /**
     * The function allowes module to transmit a packet only once time.
     */
    void disable_auto_retransmit();
   
    /**
     * The function deactives the tx interrupt generated by module
     */
    void disable_tx_interrupt();
  
    /**
    * function allowes to transmit a data with the nRF24L01P module
    * @param count dimension of data
    * @param data data to send
    * @return number of bits sent
    */
    int transmit(int count, char* data);
    
    /**
     * The function allowes to receive data from the nRF24L01P module
     * @param data variable where to store information received by module
     * @param count number of characters we want to read
     * @return -1 if the module isn't in receive mode, 0 if count is <= 0, otherwise the number
     * of chacarters read.
     */
    int receive(char *data,int count);
    

private:
    /**
     * The method reset all interrupt bits
     */
    void clear_pending_interrupt();
    
    /**
     * The function set high CE gpio in order to communicate to module to accept the
     * configuration given by spi lines.
     */
    void CE_enable();
    
    /**
     * The function set low CE gpio in order to start to communicate the new configuration 
     * to the module.
     */
    void CE_disable();
    
    /**
     * The function allowes us to set a register with a specific value
     * @param addr_register - address of the register to set
     * @param data_register - data to set into the register
     */
    void set_register(int addr_register,int data_register);
    
    /**
     * The function return the data of the register
     * @param reg - the register witch we want to know the data
     * @return data of the register
     */
    int get_register(int reg);
    
    /**
     * The function restore the old value of the CE gpio
     * @param old_ce - old value
     */
    void CE_restore(int old_ce);
    
    /**
     * The function setup all the gpio in order to create a spi communication beetween the board and the module.
     * We use:
     * - GPIOB 11 CE;
     * - GPIOB 12 CS;
     * - GPIOB 13 SCK;
     * - GPIOB 14 MISO;
     * - GPIOB 15 MOSI;
     * - GPIOA 1 IRQ;
     * We use the SPI2 interface
     */
    void setup_Gpio();
    
    /**
     * The function clear the tx queue
     */
    void flush_tx();
    
    /**
     * Function to reset all registers
     */
    void reset_module();
    
    int mode;
    /**
     * Driver spi variable
     */
    spi_driver *spi;
    
    /**
     * Enums of the possibly states of the module
     */
    typedef enum {
        NRF24L01P_UNKNOWN_MODE,
        NRF24L01P_POWER_DOWN_MODE,
        NRF24L01P_STANDBY_MODE,
        NRF24L01P_RX_MODE,
        NRF24L01P_TX_MODE,
    } NRF24L01P_mode;   

};

#endif	/* NRF24L01P_H */

