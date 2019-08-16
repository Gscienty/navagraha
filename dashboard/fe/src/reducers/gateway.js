import {
    GATEWAY_LIST_REQUEST_POST,
    GATEWAY_LIST_RECIEVE_POST,
    GATEWAY_LIST_SET,
    GATEWAY_LIST_UNSET,

    GATEWAY_SET_POST,
    GATEWAY_DELETE_POST
} from '../actions/gateway';

const initState = {
    state: GATEWAY_LIST_UNSET,
    namespace: 'unset',
    gateway: []
};

export default function gatewayReduce(state = initState, action) {

    switch (action.type) {

        case GATEWAY_LIST_REQUEST_POST:
            return Object.assign({}, state, {
            state: GATEWAY_LIST_UNSET,
            namespace: action.namespace,
            gateway: []
        });

        case GATEWAY_LIST_RECIEVE_POST:
            return Object.assign({}, state, {
            state: GATEWAY_LIST_SET,
            namespace: action.namespace,
            gateway: action.gateway
        });

        case GATEWAY_SET_POST:
            return Object.assign({}, state, {
            state: GATEWAY_LIST_UNSET,
            namespace: action.namespace,
            gateway: []
        });

        case GATEWAY_DELETE_POST:
            return Object.assign({}, state, {
            state: GATEWAY_LIST_UNSET,
            namespace: action.namespace,
            gateway: []
        });

        default:
            return state;
    }
}
