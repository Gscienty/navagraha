import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export const FUNC_LIST_REQUEST_POST = 'func_list_request_post';
export function requestFuncList(namespace) {
    return {
        type: FUNC_LIST_REQUEST_POST,
        namespace: namespace,
        func: []
    };
};

export const FUNC_LIST_RECEIVE_POST = 'func_list_receive_post';
export function receiveFuncList(namespace, received) {
    return {
        type: FUNC_LIST_RECEIVE_POST,
        namespace: namespace,
        func: received
    };
};

export const FUNC_LIST_UNSET = 'func_list_unset';
export const FUNC_LIST_SET = 'func_list_set';
export function fetchFuncList(namespace) {
    
    return function (dispatch) {
        dispatch(requestFuncList(namespace));

        return fetch(`${PREFIX_URI}/api/func/${namespace}`)
        .then(response => response.json())
        .then(json => dispatch(receiveFuncList(namespace, json)));
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
        .then(response => dispatch(fetchFuncList(funcConfig.namespace)))
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
            credentials: 'include',

        })
        .then(response => dispatch(fetchFuncList(namespace)));
    };
};

export const FUNC_POD_LIST_REQUEST_POST = 'func_pod_list_request_post';
export function requestFuncPodList(namespace, name) {
    return {
        type: FUNC_POD_LIST_REQUEST_POST
    };
};

export const FUNC_POD_LIST_RECEIVE_POST = 'func_pod_list_receive_post';
export function receiveFuncPodList(namespace, name, pods) {
    return {
        type: FUNC_POD_LIST_RECEIVE_POST,
        namespace: namespace,
        name: name,
        pods: pods
    };
};

export const FUNC_LIST_INTERVAL_FETCH_SET = 'func_list_interval_fetch_set';
export const FUNC_LIST_INTERVAL_FETCH_UNSET = 'func_list_interval_fetch_unset';

export const FUNC_LIST_INTERVAL_FETCH_SET_INTERVAL_HANDLER = 'func_list_interval_fetch_set_interval_handler';
export function intervalFuncListSetHandler(callback, interval) {
    return {
        type: FUNC_LIST_INTERVAL_FETCH_SET_INTERVAL_HANDLER,
        callback: callback,
        interval: interval
    };
};

export const FUNC_LIST_INTERCAL_FETCH_UNSET_INTERVAL_HANDLER = 'fetch_list_interval_fetch_unset_interval_handler';
export function intervalFuncListUnsetHandler() {
    return {
        type: FUNC_LIST_INTERCAL_FETCH_UNSET_INTERVAL_HANDLER
    };
};

export function intervalFuncListFetch(namespace, interval) {
    
    return function (dispatch) {
        return new Promise((resolve, reject) => 
                 dispatch(intervalFuncListSetHandler(() => {
                     dispatch(fetchFuncList(namespace));
                 }, interval)));
    };
};

