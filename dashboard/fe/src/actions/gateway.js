import fetch from 'cross-fetch';
import { PREFIX_URI } form './common';

export const GATEWAY_LIST_REQUEST_POST = 'gateway_list_request_post';
export function requestGatewayList(namespace) {
    return {
        type: GATEWAY_LIST_REQUEST_POST,
        namespace: namespace,
        gateway: []
    };
};

export const GATEWAY_LIST_RECIEVE_POST = 'gateway_list_recieve_post';
export function receiveGatewayList(namespace, received) {
    return {
        type: GATEWAY_LIST_RECIEVE_POST,
        namespace: namespace,
        gateway: received
    };
};

export const GATEWAY_LIST_UNSET = 'gateway_list_unset';
export const GATEWAY_LIST_SET = 'gateway_list_set';
export function fetchGatewayList(namespace) {

    return function (dispatch) {
        dispatch(requestGatewayList(namespace));

        return fetch(`${PREFIX_URI}/api/gateway/${namespace}`)
        .then(response => response.json())
        .then(json => dispatch(receiveGatewayList(namespace, json)));
    };
};

export const GATEWAY_SET_POST = 'gateway_set_post';
export function setGatewayAction(namespace) {
    return {
        type: GATEWAY_SET_POST,
        namespace: namespace
    };
};

export function setGateway(gatewayConfig) {

    return function (dispatch) {
        dispatch(setGatewayAction(gatewayConfig.namespace));

        return fetch(`${PREFIX_URI}/api/gateway/${gatewayConfig.namespace}`, {
            method: 'POST',
            credentials: 'include'
        })
        .then(response => dispatch(fetchGatewayList(gatewayConfig.namespace)));
    };
};

export const GATEWAY_DELETE_POST = 'gateway_delete_post';
export function deleteGatewayAction(namespace) {
    return {
        type: GATEWAY_DELETE_POST,
        namespace: namespace
    };
};

export function deleteGateway(namespace) {
    
    return function (dispatch) {
        dispatch(deleteGatewayAction(namespace));

        return fetch(`${PREFIX_URI}/api/gateway/${namespace}`, {
            method: 'DELETE',
            credentials: 'include'
        })
        .then(response => dispatch(fetchGatewayList(gatewayConfig.namespace)));
    };
};

