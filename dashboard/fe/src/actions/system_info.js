import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export const SYSTEM_INFO_NAVA_VERSION_REQUEST_POST = 'system_info_nava_version_request_post';
export function requestSystemInfoNavaVersion() {
    return {
        type: SYSTEM_INFO_NAVA_VERSION_REQUEST_POST,
        navaVersion: {
            name: 'unknow',
            version: 'unknow'
        }
    };
};

export const SYSTEM_INFO_NAVA_VERSION_RECEIVE_POST = 'system_info_nava_version_receive_post';
export function receiveSystemInfoNavaVersion(received) {
    return {
        type: SYSTEM_INFO_NAVA_VERSION_RECEIVE_POST,
        navaVersion: {
            name: received.name,
            version: received.version
        }
    };
};

export const SYSTEM_INFO_NAVA_VERSION_UNSET = 'system_info_nava_version_unset';
export const SYSTEM_INFO_NAVA_VERSION_SET = 'system_info_nava_version_set';

export function fetchSystemInfoNavaVersion() {

    return function (dispatch) {
        dispatch(requestSystemInfoNavaVersion());

        return fetch(`${PREFIX_URI}/api/system_info/nava_version`)
            .then(response => response.json(), error => console.log('An error occurred.', error))
            .then(json => dispatch(receiveSystemInfoNavaVersion(json)));
    };
};
