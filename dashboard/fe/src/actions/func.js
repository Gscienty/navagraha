import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export const FUNC_LIST_REQUEST_POST = 'func_list_request_post';
export function requestFunc(namespace) {
    return {
        type: FUNC_LIST_REQUEST_POST,
        namespace: namespace,
        func: []
    };
};

export const FUNC_LIST_RECEIVE_POST = 'func_list_receive_post';
export function receiveFunc(namespace, received) {
    return {
        type: FUNC_LIST_RECEIVE_POST,
        namespace: namespace,
        func: received
    };
};

export const FUNC_LIST_UNSET = 'func_list_unset';
export const FUNC_LIST_SET = 'func_list_set';
export function fetchFunc(namespace) {
    
    return function (dispatch) {
        dispatch(requestFunc(namespace));

        return fetch(`${PREFIX_URI}/api/func/${namespace}`)
        .then(response => response.json())
        .then(json => dispatch(receiveFunc(namespace, json)));
    };
};

export const FUNC_UP_POST = 'func_up_post';
export function upFuncAction() {
    return {
        type: FUNC_UP_POST
    };
};

export function upFunc(funcConfig) {

    return function (dispatch) {
        dispatch(upFuncAction());

        return fetch(`${PREFIX_URI}/api/func/${funcConfig.namespace}`, {
            method: 'POST',
            credentials: 'include',
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(funcConfig)
        })
        .then(response => dispatch(fetchFunc(funcConfig.namespace)))
    };
};

export const FUNC_DOWN_POST = 'func_down_post';
export function downFuncAction() {
    return {
        type: FUNC_DOWN_POST
    };
};

export function downFunc(namespace, name) {
    
    return function (dispatch) {
        dispatch(downFuncAction());

        return fetch(`${PREFIX_URI}/api/func/${namespace}/${name}`, {
            method: 'DELETE',
            credentials: 'include'
        })
        .then(response => dispatch(fetchFunc(namespace)));
    };
};

