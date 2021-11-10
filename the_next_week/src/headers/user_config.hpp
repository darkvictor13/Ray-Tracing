#ifndef USER_CONFIG
#define USER_CONFIG

/**
 * @file user_config.hpp
 * 
 * @author Victor Emanuel Almeida (victoralmeida2001@hotmail.com)
 * @brief Arquivo onde o usuário configura parâmetros que
 * alteram a geração da imagem final,
 * bem como o funcionamento da aplicação
 * @version 0.1
 * @date 01/11/2021
 */

#define INVALID_VALUE -1

/**
 * @brief Define se o programa deve ou não mostrar
 * informações de Debug
 */
#define DEBUG_VAR 1

/**
 * @brief Caminho para a pasta onde as imagens devem ser salvas
 */
#define IMAGE_PATH "../images/"
/**
 * @brief Caso o usuário não queira dar um nome a imagem,
 * esse será o nome da mesma.
 */
#define DEFAULT_FILE_NAME "bola.ppm"

/**
 * @brief Largura da imagem.
 * 
 * Quantidade de colunas em pixels
 */
#define IMAGE_WIDTH  400
/**
 * @brief Define a proporção entre linhas e colunas da imagem
 */
#define ASPECT_RATIO (16.0 / 9.0)

/**
 * @brief Quantidade de nucleos que sua CPU possui
 * para processamento paralelo
 */
#define CPU_CORES 4

#if DEBUG_VAR == INVALID_VALUE || \
IMAGE_WIDTH == INVALID_VALUE || \
MAX_DEPTH == INVALID_VALUE || CPU_CORES == INVALID_VALUE

#error Arquivo de configuracao nao foi editado de forma correta
#endif

#endif // USER_CONFIG
