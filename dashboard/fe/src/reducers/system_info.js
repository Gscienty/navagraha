import {
    SYSTEM_INFO_NAVA_VERSION_REQUEST_POST,
    SYSTEM_INFO_NAVA_VERSION_RECEIVE_POST,
    SYSTEM_INFO_NAVA_VERSION_UNSET,
    SYSTEM_INFO_NAVA_VERSION_SET
} from '../actions/system_info'


const initState = {
    navaVersion: {
        state: SYSTEM_INFO_NAVA_VERSION_UNSET,
        name: 'unknow',
        version: 'unknow'
    }
}

export default function systemInfoReduce(state = initState, action) {
    
    switch (action.type) {
        case SYSTEM_INFO_NAVA_VERSION_REQUEST_POST:
            return Object.assign({}, state, {
                navaVersion: {
                    state: SYSTEM_INFO_NAVA_VERSION_UNSET
                }
            });

        case SYSTEM_INFO_NAVA_VERSION_RECEIVE_POST:
            return Object.assign({}, state, {
                navaVersion: {
                    state: SYSTEM_INFO_NAVA_VERSION_SET,
                    name: action.navaVersion.name,
                    version: action.navaVersion.version
                }
            });

        default:
            return state;
    }
}
