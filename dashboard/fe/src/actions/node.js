import fetch from 'cross-fetch';
import { PREFIX_URI } from './common';

export const NODE_LIST_REQUEST_POST = 'node_list_request_post';
export function requestNodeList() {
    return {
        type: NODE_LIST_REQUEST_POST,
        nodes: []
    };
};

export const NODE_LIST_RECEIVE_POST = 'node_list_receive_post';
export function receiveNodeList(received) {
    return {
        type: NODE_LIST_RECEIVE_POST,
        nodes: received
    };
};

export const NODE_LIST_UNSET = 'node_list_unset';
export const NODE_LIST_SET = 'node_list_set';

export function fetchNodeList() {

    return function(dispatch) {
        dispatch(requestNodeList());

        return fetch(`${PREFIX_URI}/api/node`, {
            method: 'GET',
        })
        .then(response => response.json())
        .then(json => dispatch(receiveNodeList(json)));
    };
};
