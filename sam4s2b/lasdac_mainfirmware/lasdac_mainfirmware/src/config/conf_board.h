/**
 * \file
 *
 * \brief User board configuration template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#ifndef CONF_BOARD_H
#define CONF_BOARD_H

#define PIN_SHUTTER IOPORT_CREATE_PIN(PIOA,26)
#define PIN_STATUSLED IOPORT_CREATE_PIN(PIOA,24)

/*! SPI MISO pin definition. */
#define SPI_MISO_GPIO        (PIO_PA12_IDX)
#define SPI_MISO_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)
/*! SPI MOSI pin definition. */
#define SPI_MOSI_GPIO        (PIO_PA13_IDX)
#define SPI_MOSI_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)

#define SPI_NPCS0_GPIO			(PIO_PA11_IDX)
#define SPI_NPCS0_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)

/*! SPI SPCK pin definition. */
#define SPI_SPCK_GPIO        (PIO_PA14_IDX)
#define SPI_SPCK_FLAGS       (PIO_PERIPH_A | PIO_DEFAULT)

#endif // CONF_BOARD_H
