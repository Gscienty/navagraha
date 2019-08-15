import React from 'react';
import './App.css';
import { connect } from 'react-redux';
import {
    fetchSystemInfoNavaVersion,
    SYSTEM_INFO_NAVA_VERSION_UNSET
} from './actions/system_info'

class App extends React.Component {

    componentWillMount() {
        if (this.props.navaVersion.state === SYSTEM_INFO_NAVA_VERSION_UNSET) {
            this.props.dispatch(fetchSystemInfoNavaVersion());
        }
    }

    render() {
        return (
            <div className="App">
                Hello { this.props.navaVersion.name } { this.props.navaVersion.version }
            </div>
        );
    }
};

export default connect(({ systemInfo }) => ({
    navaVersion: systemInfo.navaVersion
}))(App);
