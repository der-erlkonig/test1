
/**
 * @struct     Host_env
 * @brief      current environment of the camera
 */
struct Host_env{
    
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