/* Private variables ---------------------------------------------------------*/
char str1[60];
/* USER CODE END PV */

/* USER CODE BEGIN 1 */
uint8_t status;
/* USER CODE END 1 */
port_init();
status = ds18b20_init(SKIP_ROM);
sprintf(str1,"Init Status: %drn",status);
HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);

uint8_t status;
uint8_t dt[8];
uint16_t raw_temper;
float temper;
char c;

while (1)
{
/* USER CODE BEGIN 3 */
ds18b20_MeasureTemperCmd(SKIP_ROM, 0);
HAL_Delay(800);
ds18b20_ReadStratcpad(SKIP_ROM, dt, 0);
sprintf(str1,"STRATHPAD: %02X %02X %02X %02X %02X %02X %02X %02X; ",
dt[0], dt[1], dt[2], dt[3], dt[4], dt[5], dt[6], dt[7]);
HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
sprintf(str1,"rn");
HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
HAL_Delay(150);
}
/* USER CODE END 3 */


HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
raw_temper = ((uint16_t)dt[1]<<8)|dt[0];
if(ds18b20_GetSign(raw_temper)) c='-';
else c='+';
temper = ds18b20_Convert(raw_temper);
sprintf(str1,"Raw t: 0x%04X; t: %c%.2frn", raw_temper, c, temper);
HAL_UART_Transmit(&huart1,(uint8_t*)str1,strlen(str1),0x1000);
HAL_Delay(150);