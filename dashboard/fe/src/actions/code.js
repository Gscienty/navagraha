import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export const CODE_TEMPLATE_LIST_REQUEST_POST = 'code_template_list_request_post';
export function requestCodeTemplateList() {
    return {
        type: CODE_TEMPLATE_LIST_REQUEST_POST
    };
};

export const CODE_TEMPLATE_LIST_RECEIVE_POST = 'code_template_list_receive_post';
export function receiveCodeTemplateList(received) {
    return {
        type: CODE_TEMPLATE_LIST_RECEIVE_POST,
        templateList: received
    };
};

export const CODE_TEMPLATE_LIST_SET = 'code_template_list_set';
export const CODE_TEMPLATE_LIST_UNSET = 'code_template_list_unset';
export function fetchCodeTemplateList() {
    
    return function (dispatch) {
        dispatch(requestCodeTemplateList());

        return fetch(`${PREFIX_URI}/api/template/type`)
        .then(response => response.json())
        .then(json => dispatch(receiveCodeTemplateList(json)));
    };
};

export const CODE_TEMPLATE_REQUEST_POST = 'code_template_request_post';
export function codeTemplateRequest() {
    return {
        type: CODE_TEMPLATE_REQUEST_POST
    };
};

export const CODE_TEMPLATE_RECEIVE_POST = 'code_template_receive_post';
export function codeTemplateReceive(type, content) {
    return {
        type: CODE_TEMPLATE_RECEIVE_POST,
        templateType: type,
        templateContent: content
    }
}

export const CODE_TEMPLATE_SELECTED_SET = 'code_template_selected_set';
export const CODE_TEMPLATE_SELECTED_UNSET = 'code_template_selected_unset';
export function fetchCodeTemplate(type) {

    return function (dispatch) {
        dispatch(codeTemplateRequest());

        return fetch(`${PREFIX_URI}/api/template/content/${type}`)
        .then(response => response.json())
        .then(json => dispatch(codeTemplateReceive(json.type, json.content)));
    };
};

export const CODE_SUBMIT_TOGGLE = 'code_submit_toggle';
export function submitToggle() {
    return {
        type: CODE_SUBMIT_TOGGLE
    };
};

export const CODE_SUBMIT_SET = 'code_submit_set';
export const CODE_SUBMIT_UNSET = 'code_submit_unset';

export const CODE_RESET_CODE_INFO = 'code_reset_code_info';
export function resetCode() {
    return {
        type: CODE_RESET_CODE_INFO
    };
};

export const CODE_SUBMIT_CODE_INFO = 'code_submit_code';
export function submitCode(type, content) {
    return {
        type: CODE_SUBMIT_CODE_INFO,
        codeInfo: {
            type: type,
            content: content
        }
    };
};

export const CODE_METADATA_SET = 'code_metadata_set';
export const CODE_METADATA_UNSET = 'code_metadata_unset';

export const CODE_RESET_METADATA = 'code_reset_metadata';
export function codeResetMetadata() {
    return {
        type: CODE_RESET_METADATA
    };
};

export const CODE_SUBMIT_METADATA = 'code_submit_metadata';
export function codeChangeMetadata(metadata) {
    return {
        type: CODE_SUBMIT_METADATA,
        metadata: metadata
    };
};

export const CODE_BUILD_WAITING = 'code_build_waiting';
export const CODE_BUILD_RUNNING = 'code_build_running';

export const CODE_BUILDING_RUNNING = 'code_building_running';
export function codeBuildingRunning() {
    return {
        type: CODE_BUILDING_RUNNING
    };
};

export const CODE_BUILDING_FINISHED = 'code_building_finished';
export function codeBuildingFinished() {
    return {
        type: CODE_BUILDING_FINISHED
    };
};

export const CODE_BUILDING_PROCESS = 'code_building_process';
export function codeBuildingProcess(msg) {
    let spliter = msg.indexOf(':');
    let tmp = msg.indexOf(' ') + 1;
    let process = msg.substr(tmp, spliter - 1 - tmp);
    let nums = process.split('/');

    return {
        type: CODE_BUILDING_PROCESS,
        buildingProcess: parseFloat(nums[0]) / parseFloat(nums[1]),
        buildingInfo: msg.substr(spliter + 1)
    };
};

export function codeBuild(codeInfo) {

    return function (dispatch) {
        dispatch(codeBuildingRunning());

        return fetch(`${PREFIX_URI}/api/topic`, {
            method: 'POST',
            credentials: 'include'
        })
        .then(response => response.json())
        .then(json => {
            let sock = new WebSocket(`ws://${window.location.host}/api/ws-topic/${json.topic}`);

            sock.onmessage = msg => {
                let spliter = msg.data.indexOf(':');
                let eve = msg.data.substr(0, spliter);
                let payload = msg.data.substr(spliter + 1);

                switch (eve) {
                case 'complete':
                    dispatch(codeBuildingFinished());
                    break;

                case 'data':
                    let json = JSON.parse(payload);
                    if (typeof json.stream !== 'undefined' && json.stream.startsWith('Step')) {
                        dispatch(codeBuildingProcess(json.stream));
                    }
                    break;

                default:
                    break;
                };
            };

            sock.onclose = () => {
                dispatch(codeBuildingFinished());
            }

            return fetch(`${PREFIX_URI}/api/repo/build/${json.topic}`, {
                method: 'POST',
                credentials: 'include',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    type: codeInfo.type,
                    name: codeInfo.name,
                    version: codeInfo.version,
                    content: codeInfo.content
                })
            });
        })
    }
}
