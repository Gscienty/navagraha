import {
    FUNC_LIST_REQUEST_POST,
    FUNC_LIST_RECEIVE_POST,
    FUNC_UP_POST,
    FUNC_DOWN_POST,
    FUNC_LIST_SET,
    FUNC_LIST_UNSET,

    FUNC_LIST_INTERVAL_FETCH_SET_INTERVAL_HANDLER,
    FUNC_LIST_INTERCAL_FETCH_UNSET_INTERVAL_HANDLER,
    FUNC_LIST_INTERVAL_FETCH_SET,
    FUNC_LIST_INTERVAL_FETCH_UNSET,

    FUNC_DETAIL_SET,
    FUNC_DETAIL_UNSET,
    FUNC_DETAIL_FETCH_RECEIVE,
    FUNC_DETAIL_FETCH_REQUEST
} from '../actions/func';

const initState = {
    state: FUNC_LIST_UNSET,
    namespace: 'unset',
    func: [],
    fetchInterval: 0,
    fetchIntervalState: FUNC_LIST_INTERVAL_FETCH_UNSET,

    funcDetail: null,
    funcDetailState: FUNC_DETAIL_UNSET
};

export default function funcReduce(state = initState, action) {

    switch (action.type) {

        case FUNC_LIST_REQUEST_POST:
            return state;

        case FUNC_LIST_RECEIVE_POST:
            return Object.assign({}, state, {
            type: FUNC_LIST_SET,
            namespace: action.namespace,
            func: action.func
        });

        case FUNC_UP_POST:
            return state;

        case FUNC_DOWN_POST:
            return state;

        case FUNC_LIST_INTERVAL_FETCH_SET_INTERVAL_HANDLER:
            if (state.fetchIntervalState === FUNC_LIST_INTERVAL_FETCH_SET) {
            return state;
        }
        else {
            return Object.assign({}, state, {
                fetchInterval: setInterval(action.callback, action.interval),
                fetchIntervalState: FUNC_LIST_INTERVAL_FETCH_SET
            });
        };

        case FUNC_LIST_INTERCAL_FETCH_UNSET_INTERVAL_HANDLER:
            if (state.fetchIntervalState === FUNC_LIST_INTERVAL_FETCH_UNSET) {
            return state;
        }
        else {
            clearInterval(state.fetchInterval);
            return Object.assign({}, state, {
                fetchIntervalState: FUNC_LIST_INTERVAL_FETCH_UNSET
            });
        }

        case FUNC_DETAIL_FETCH_RECEIVE:
            return Object.assign({}, state, {
            funcDetail: action.detail,
            funcDetailState: FUNC_DETAIL_SET
        });

        case FUNC_DETAIL_FETCH_REQUEST:
            return Object.assign({}, state, {
            funcDetail: null,
            funcDetailState: FUNC_DETAIL_UNSET
        });

        default:
            return state;
    };
};

