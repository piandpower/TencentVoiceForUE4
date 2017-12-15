//
//  GCloudVoiceVersion.h
//  gcloud_voice
//
//  Created by cz on 15/10/19.
//  Copyright © 2015年 gcloud. All rights reserved.
//

#ifndef gcloud_voice_GCloudVoiceVersion_h_
#define gcloud_voice_GCloudVoiceVersion_h_

#define GCLOUD_VOICE_VERSION "GCloudVoice1.1.12.159258"

namespace gcloud_voice
{
enum {
    VER_MAJOR = 1,
    VER_MINOR = 1,
    VER_FIX   = 12,
    
    VER_SVN   = 159258,
    
    VER_BUF_LEN = 1024,
};



const char * gvoice_get_version();
}
#endif /* gcloud_voice_GCloudVoiceVersion_h_ */
