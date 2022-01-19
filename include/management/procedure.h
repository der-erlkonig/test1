/**
 * @file include/management/procedure.h
 * @brief      This file implements procedure.
 * @version    0.0.2
 * @author     Ji Xiangyu
 * @date       2022.1.15
 */

/**
 * @enum    Mode
 * @brief   Camera travel mode
 */
enum{
    ABSOLUTE=0, /*!< absolute move */
    CONTINUOUS  /*!< continuous move */
};

/**
 * @brief      camera ptz status
 */
struct PTZ_State{
    char* xaddr;/*!< the media service address, used as the unique identifier */
    float pan;/*!< (target/current) pan degree */
    float tilt;/*!< (target/current) tilt degree */
    float zoom;/*!< (target/current) zoom degree */
    int switcher;/*!< whether the camera runs in absolute or continuous mode */
    int running;/*!< whether the camera is targeting or stand at the given state. Always false if using absolute move*/
};

/**
 * @struct     Host_env
 * @brief      current environment of the camera
 */
struct Host_env{
    int ptz_support;/*!< whether camera support ptz control */
    struct PTZ_State* status; /*!< camera ptz status, NULL if not supported */
    char* imgpath;/*!< local path of snapshot */
    char* stream;/*!< ipc stream uri */
};

/**
 * @typedef   funtion
 * @par prototype
 *     void* (*)(struct Host_env* env, void* params);
 * @brief     prototype of registered function
 * @param[in] env environment of method excution
 * @param[in] params extra parameters of method
 * @return    return value of method
 */
typedef void* (*function)(struct Host_env* env, void* params);

/**
 * @enum    trigger
 * @brief   trigger of method excution, including following scope
 */
enum{
    START=0,   /*!< when the whole scan pattern is going to be established */
    PRE_TURN,  /*!< when a single turn of scan starts */
    PRE_STATE, /*!< when the camera's state will be changed, including pan/tilt/zoom */
    PRE_SHOT,  /*!< when a snapshot is going to be captured */
    POST_SHOT, /*!< when a snapshot is captured */
    POST_STATE,/*!< when the camera's state has been changed */
    POST_TURN, /*!< when a camera has finished a single scan turn */
    END        /*!< when the whole scan pattern has been completed */
};

