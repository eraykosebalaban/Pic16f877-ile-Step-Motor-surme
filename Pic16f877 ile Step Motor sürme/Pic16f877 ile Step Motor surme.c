#include<16f877.h>

#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD

#use delay(clock = 4000000)

#define use_portb_lcd TRUE
#include<lcd.c>

#use fast_io(a)
#use fast_io(b)
#use fast_io(d)

#define ileri pin_a0
#define geri pin_a1

unsigned int ADIM=1; // Step motorun ad?m?n? 1 den ba?lat?yoruz.
char durum;

void main(){
setup_psp(PSP_DISABLED);
setup_timer_1(T1_DISABLED);
setup_timer_2(T2_DISABLED,0,1);
setup_adc_ports(NO_ANALOGS);
setup_adc(ADC_OFF);
setup_ccp1(CCP_OFF);
setup_ccp2(CCP_OFF);

set_tris_a(0x03);
set_tris_b(0x00);
set_tris_d(0x00);

output_b(0x00);
output_d(0x00);

lcd_init();
delay_ms(10);

ADIM = 0;

while(true){

if(input(ileri)){
 delay_ms(100);
 ADIM = ADIM+1;
 durum=1;
 
if(ADIM==9){
 
 ADIM=1;
 durum=1;

}
}

if(input(geri)){
 delay_ms(100);
 ADIM = ADIM - 1;
 durum=2;

if(ADIM==0){

 ADIM=8;
 durum=2;

}
}

if(input(ileri) & input(geri)){ //?leri ve geri butona ayn? anda bas?ld?ysa 4.durum (Konum:Hata) ger?ekle?sin.
 durum=4;
}

if(!input(ileri) & !input(geri)){ //?leri ve geri butona bas?lmam??sa 3. Durum(Konum:Bo?ta) ger?ekle?sin.
 durum=3;
}

delay_ms(500);

switch(ADIM){

case 1:
 output_d(0b00000001);
 break;

case 2:
 output_d(0b00000011);
 break;
 
case 3:
 output_d(0b00000010);
 break;
 
case 4:
 output_d(0b00000110);
 break;
 
case 5:
 output_d(0b00000100);
 break;
 
case 6:
 output_d(0b00001100);
 break;
 
case 7:
 output_d(0b00001000);
 break;
 
case 8:
 output_d(0b00001001);
 break;
 
}
delay_ms(10);

switch(durum){
 case 1:
 printf(lcd_putc,"\fADIM=%u\nKonum:Ileri",ADIM);
 break;
 
 case 2:
 printf(lcd_putc,"\fADIM=%u\nKonum:Geri",ADIM);
 break;
 
 case 3:
 printf(lcd_putc,"\fADIM=%u\nKonum:Bosta",ADIM);
 break;
 case 4:
 printf(lcd_putc,"\fADIM=%u\nKonum:Hata",ADIM);
 break;
 
}
delay_ms(10);



}

}

