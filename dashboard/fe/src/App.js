import React from 'react';
import './App.css';
import { connect } from 'react-redux';
import {
    fetchSystemInfoNavaVersion,
    SYSTEM_INFO_NAVA_VERSION_UNSET
} from './actions/system_info';
import NamespaceSelector from './components/namespace_selector';
import FuncRepoList from './components/gateway_repo_list';

class App extends React.PureComponent {

    constructor(props) {
        super(props);

        if (this.props.navaVersion.state === SYSTEM_INFO_NAVA_VERSION_UNSET) {
            this.props.dispatch(fetchSystemInfoNavaVersion());
        }
    }

    render() {
        return (
            <div className="App">
                <NamespaceSelector />
                Hello { this.props.navaVersion.name } { this.props.navaVersion.version }
                <FuncRepoList />
            </div>
        );
    }
};

export default connect(({ systemInfo }) => ({
    navaVersion: systemInfo.navaVersion
}))(App);

