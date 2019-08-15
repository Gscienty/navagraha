import {
    FUNC_LIST_REQUEST_POST,
    FUNC_LIST_RECEIVE_POST,
    FUNC_UP_POST,
    FUNC_DOWN_POST,
    FUNC_LIST_SET,
    FUNC_LIST_UNSET
} from '../actions/func';

const initState = {
    state: FUNC_LIST_UNSET,
    namespace: 'unset',
    func: []
};

export default function funcReduce(state = initState, action) {

    switch (action.type) {

        case FUNC_LIST_REQUEST_POST:
            return Object.assign({}, state, {
            type: FUNC_LIST_UNSET,
            namespace: action.namespace
        });

        case FUNC_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            type: FUNC_LIST_SET,
            namespace: action.namespace,
            func: action.func
        });

        case FUNC_UP_POST:
            return Object.assign({}, state, {
            type: FUNC_LIST_UNSET,
        });

        case FUNC_DOWN_POST:
            return Object.assign({}, state, {
            type: FUNC_LIST_UNSET,
        });

        default:
            return state;
    };
};
