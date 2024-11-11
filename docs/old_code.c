/*****************************************************
This program was produced by the
CodeWizardAVR V2.04.8b Evaluation
Automatic Program Generator
© Copyright 1998-2010 Pavel Haiduc, HP InfoTech s.r.l.
http://www.hpinfotech.com

Project :
Version :
Date    : 04.09.2010
Author  : Freeware, for evaluation and non-commercial use only
Company :
Comments:


Chip type               : ATtiny44
AVR Core Clock frequency: 8,000000 MHz
Memory model            : Tiny
External RAM size       : 0
Data Stack size         : 64
*****************************************************/

#include <tiny44.h>

#include <delay.h>
unsigned char pot_value = 63;   // положение потенциометра
unsigned char current_vol = 63; // текущий уровень громкости
unsigned char pot_vol = 63;     // последняя выставленная при помощи потенциометра громкость
unsigned char mute = 0;         // флаг выключения звука

// Счетчик битов RC5
unsigned char sct_bit = 0;

// Буффер RC5
unsigned char RC5_buffer[14];

// Временные пределы
#define Tmin 40 // длинный промежуток
#define Tmax 68
#define TminK 22 // короткий промежуток
#define TmaxK 34

#define ONOFF 0xC
#define MUTE 0xD
#define TVAV 0x38
#define OK 0x25
#define COMMONVOLPLUS 0x10
#define COMMONVOLMINUS 0x11
#define VOLPLUS 2
#define VOLMINUS 1

// Флаг центра
unsigned char centre = 0;
// Флаг попадания в промежутки
unsigned char not_korr = 0;
// число в счетчике таймера
unsigned char Timer = 0;
// переменные кодов
unsigned char startbit2 = 0;
unsigned char trigger = 0;
unsigned int device = 0;
unsigned char command = 0;

unsigned char read_adc(unsigned char adc_input);



char set_vol(char vol)
{
    unsigned char diff, act, cvol;
    cvol = PORTA;
    diff = vol ^ cvol;
    act = diff & vol;
    // ослабление на 1дБ
    if (act & 1)
        PORTA .0 = 1;
    // ослабление на 2дБ
    if (act & 2)
        PORTA .1 = 1;
    // ослабление на 4дБ
    if (act & 4)
        PORTA .2 = 1;
    // ослабление на 8дБ
    if (act & 8)
        PORTA .3 = 1;
    // ослабление на 16дБ
    if (act & 16)
        PORTA .4 = 1;
    // ослабление на 32дБ
    if (act & 32)
        PORTA .5 = 1;
    delay_ms(5); // задержка для того, чтобы не было кратковременных скачков громкости
    act = diff & cvol;
    // ослабление на 1дБ
    if (act & 1)
        PORTA .0 = 0;
    // ослабление на 2дБ
    if (act & 2)
        PORTA .1 = 0;
    // ослабление на 4дБ
    if (act & 4)
        PORTA .2 = 0;
    // ослабление на 8дБ
    if (act & 8)
        PORTA .3 = 0;
    // ослабление на 16дБ
    if (act & 16)
        PORTA .4 = 0;
    // ослабление на 32дБ
    if (act & 32)
        PORTA .5 = 0;
    delay_ms(200);
    return vol;
}

// Pin change 0-7 interrupt service routine
interrupt[PC_INT0] void pin_change_isr0(void)
{
    // Place your code here
    Timer = TCNT0; // запоминаем значение счетчика       /////////////////////////////////////
    TCNT0 = 0;     // обнуляем счетчик
    not_korr = 1;

    switch (sct_bit)
    {

    case 0:
        TCCR0B = 0x04;                  // запускаем таймер  (31.250 KHz)  //////////////////////////////////////////////
        RC5_buffer[sct_bit] = !PINA .7; // записываем в эл.массива
        sct_bit++;
        centre = 1;
        break;

    default:

        if ((Timer > TminK) && (Timer < TmaxK)) // проверка короткого промежутка
        {
            if (centre)
            {
                centre = 0;
                not_korr = 0;
            }
            else
            {
                centre = 1;
                RC5_buffer[sct_bit] = !PINA .7;
                sct_bit++;
                not_korr = 0;
            };
        };

        if ((Timer > Tmin) && (Timer < Tmax))
        { // проверка длинного промежутка
            RC5_buffer[sct_bit] = !PINA .7;
            sct_bit++;
            not_korr = 0;
        };

        if (not_korr == 1)
        { // если не попали ни в один из промежутков то
            char i = 0;
            GIMSK |= 0x00; // запрещаем прерывания по изм. по входу (разрешим в обработчике прерывания по переполнению счетчика)
            TCCR0B = 0x00;
            TCNT0 = 0;
            sct_bit = 0;
            // очищаем буффер
            for (i = 0; i < 14; i++)
            {
                RC5_buffer[i] = 0;
            };
            // отправляем NO Correct takte (отправлять не обязательно - для себя...)

            // putsf ("T");   //---------->>>>>>>>>>>>>>
        };

        if (sct_bit == 14)
        { // если бит последний то

            TCCR0B = 0x00; // останавливаем таймер
            TCNT0 = 0;
            sct_bit = 0;
            // формируем из массива соответствующие коды
            startbit2 = RC5_buffer[1];
            trigger = RC5_buffer[2];

            device = (RC5_buffer[3] << 4) | (RC5_buffer[4] << 3) | (RC5_buffer[5] << 2) | (RC5_buffer[6] << 1) | RC5_buffer[7];
            command = (RC5_buffer[8] << 5) | (RC5_buffer[9] << 4) | (RC5_buffer[10] << 3) | (RC5_buffer[11] << 2) | (RC5_buffer[12] << 1) | RC5_buffer[13];

			switch (command)
			{
				
#ifdef VOLPLUS
				case VOLPLUS: // увеличение локальной громкости
#endif	
				case COMMONVOLPLUS: // увеличение громкости
				{
					if (current_vol > 0)
					{
						current_vol = set_vol(current_vol - 1);
						if (mute > 0)
						{
							mute = 0;
						}
					}
					break;
				}
				
#ifdef VOLMINUS
				case VOLMINUS: // уменьшение локальной громкости
#endif	
				case COMMONVOLMINUS: // уменьшение громкости
				{
					if (current_vol < 63)
					{
						current_vol = set_vol(current_vol + 1);
						if (mute > 0)
						{
							mute = 0;
						}
					}
					break;
				}

#ifdef ONOFF
				case 12: // power off
				{
					mute = set_vol(63);
					delay_ms(250);
					if(PINB & 1)
					{
						PORTB &= 0xFE;
					}
					else
					{
						current_vol = set_vol(read_adc(6));
						mute = 0;
						PORTB |= 1;
					}

				
//					PORTB |= 1;
//					delay_ms(200);
//					PORTB &= 0xFE;
					break;
				}
#endif

#ifdef TVAV
				case TVAV: // A/V
				{
					PORTB |= (1 << 2);
					delay_ms(600);
					PORTB &= ~(1 << 2);
					break;
				}
#endif

				case MUTE: // мьют
				{
					mute = set_vol(63);
					delay_ms(250);
					if(PINB & 2)
					{
						PORTB &= 0xFD;
					}
					else
					{
						current_vol = set_vol(current_vol);
						mute = 0;
						PORTB |= 2;
					}
					
/*					if (mute == 0)
					{
						mute = set_vol(63);
					}
					else
					{
						current_vol = set_vol(current_vol);
						mute = 0;
					}
*/					break;
				}
				
#ifdef OK
				case OK:
				{
					current_vol = set_vol(read_adc(6));
					mute = 0;
				}
#endif
		
				// пауза не обязательно - чтобы реакция кнопок была помедленнее...
			};

            // сбрасываем флаг прерывания по входу INT0
            GIFR = 0x10;
        };
    };
}

// Timer 0 overflow interrupt service routine
interrupt[TIM0_OVF] void timer0_ovf_isr(void)
{
    // Place your code here
    char i = 0;
    GIMSK |= 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0;
    sct_bit = 0;
    // очищаем буффер
    for (i = 0; i < 14; i++)
    {
        RC5_buffer[i] = 0;
    };
    // отправляем NO Correct block - для отладки...
    //  putsf ("B");  //----------->>>>>>>
    // LED_OFF;
    GIMSK |= 0x10; // разрешаем прерывания по входу
    GIFR = 0x10;   // сбрасываем флаг прерывания (если произошло)
}

#define ADC_VREF_TYPE 0x00

// Read the 8 most significant bits
// of the AD conversion result
unsigned char read_adc(unsigned char adc_input)
{
    ADMUX = (adc_input & 0x3f) | ADC_VREF_TYPE;
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA |= 0x40;
    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10) == 0)
        ;
    ADCSRA |= 0x10;
    return ADCH >> 2; // уменьшаем диапазон значений АЦП с 0-255 до 0-63
}

// Timer1 overflow interrupt service routine
interrupt[TIM1_OVF] void timer1_ovf_isr(void)
{
    // Регулировка громкости при помощи потенциометра
    pot_value = read_adc(6);
    if (pot_value != pot_vol)
    {
        current_vol = set_vol(pot_value);
        pot_vol = current_vol;
        if (mute > 0)
        {
            mute = 0;
        }
    }
}

// Declare your global variables here

void main(void)
{
// Declare your local variables here

// Crystal Oscillator division factor: 1
#pragma optsize -
    CLKPR = 0x80;
    CLKPR = 0x00;
#ifdef _OPTIMIZE_SIZE_
#pragma optsize +
#endif

    // Input/Output Ports initialization
    // Port A initialization
    // Func7=In Func6=In Func5=Out Func4=Out Func3=Out Func2=Out Func1=Out Func0=Out
    // State7=T State6=T State5=1 State4=1 State3=1 State2=1 State1=1 State0=1
    PORTA = 0x3F;
    DDRA = 0x3F;

    // Port B initialization
    // Func3=In Func2=In Func1=In Func0=In
    // State3=T State2=T State1=T State0=T
    PORTB = 0x00;
    DDRB = 0x03;

    // Timer/Counter 0 initialization
    // Clock source: System Clock
    // Clock value: Timer 0 Stopped
    // Mode: Normal top=FFh
    // OC0A output: Disconnected
    // OC0B output: Disconnected
    TCCR0A = 0x00;
    TCCR0B = 0x00;
    TCNT0 = 0x00;
    OCR0A = 0x00;
    OCR0B = 0x00;

    // Timer/Counter 1 initialization
    // Clock source: System Clock
    // Clock value: 7,813 kHz
    // Mode: Normal top=FFFFh
    // OC1A output: Discon.
    // OC1B output: Discon.
    // Noise Canceler: Off
    // Input Capture on Falling Edge
    // Timer1 Overflow Interrupt: On
    // Input Capture Interrupt: Off
    // Compare A Match Interrupt: Off
    // Compare B Match Interrupt: Off
    TCCR1A = 0x00;
    TCCR1B = 0x02;
    TCNT1H = 0x00;
    TCNT1L = 0x00;
    ICR1H = 0x00;
    ICR1L = 0x00;
    OCR1AH = 0x00;
    OCR1AL = 0x00;
    OCR1BH = 0x00;
    OCR1BL = 0x00;

    // External Interrupt(s) initialization
    // INT0: Off
    // Interrupt on any change on pins PCINT0-7: On
    // Interrupt on any change on pins PCINT8-11: Off
    MCUCR = 0x00;
    PCMSK0 = 0x80;
    GIMSK = 0x10;
    GIFR = 0x10;

    // Timer/Counter 0 Interrupt(s) initialization
    TIMSK0 = 0x01;
    // Timer/Counter 1 Interrupt(s) initialization
    TIMSK1 = 0x01;

    // Universal Serial Interface initialization
    // Mode: Disabled
    // Clock source: Register & Counter=no clk.
    // USI Counter Overflow Interrupt: Off
    USICR = 0x00;

    // Analog Comparator initialization
    // Analog Comparator: Off
    // Analog Comparator Input Capture by Timer/Counter 1: Off
    ACSR = 0x80;
    ADCSRB = 0x00;

    // ADC initialization
    // ADC Clock frequency: 62,500 kHz
    // ADC Bipolar Input Mode: Off
    // ADC Auto Trigger Source: ADC Stopped
    // Only the 8 most significant bits of
    // the AD conversion result are used
    // Digital input buffers on ADC0: On, ADC1: On, ADC2: On, ADC3: On
    // ADC4: On, ADC5: On, ADC6: On, ADC7: On
    DIDR0 = 0x00;
    ADMUX = ADC_VREF_TYPE & 0xff;
    ADCSRA = 0x87;
    ADCSRB &= 0x6F;
    ADCSRB |= 0x10;

    // начальная установка громкости в соответствии с уровнем, выставленным при помощи потенциометра.
    pot_value = read_adc(6);
    current_vol = set_vol(pot_value);
    pot_vol = current_vol;

// Global enable interrupts
#asm("sei")

    while (1)
    {
        // Place your code here
    }
}
