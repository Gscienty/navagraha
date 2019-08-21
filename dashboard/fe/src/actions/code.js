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

export function codeBuild(codeInfo) {

    return function (dispatch) {
        dispatch(codeBuildingRunning());

        return fetch(`${PREFIX_URI}/api/repo/build/${codeInfo.type}`, {
            method: 'POST',
            credentials: 'include',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                name: codeInfo.name,
                version: codeInfo.version,
                content: codeInfo.getContent
            })
        })
        .then(response => dispatch(codeBuildingFinished()));
    }
}
